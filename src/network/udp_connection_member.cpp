#include "udp_connection_member.h"
#include "jsoncpp/json.h"
#include "string_utility.h"
namespace network
{
udp_connection::member::member( udp_connection & server, udp::endpoint const & end_point )
    : _server( server )
    , _udp_socket( _io_service, end_point )
    , _client_manager( server )
{
    _remote_buffer.fill( 0 );

    _read( );

    _update_io_service = std::thread( [ this ]
    {
        while ( _is_update )
        {
            _io_service.run( );
            _io_service.reset( );
        }
    } );
}
udp_connection::member::member( udp_connection & server )
    : udp_connection::member( server, udp::endpoint( )/*空のendpointを送るとopenやlocal_endpointも設定してくれるようです。*/ )
{
}
udp_connection::member::member( udp_connection& server, int const & port_num )
    : udp_connection::member( server, udp::endpoint( udp::v4( ), port_num ) )
{
}
udp_connection::member::~member( )
{
    _kill( );
}
void udp_connection::member::write( network_handle const & handle, Json::Value const & send_data )
{
    write( handle, Json::FastWriter( ).write( send_data ) );
}
void udp_connection::member::write( network_handle const & handle, std::string const & send_data )
{
    write( handle, send_data.c_str( ), send_data.size( ) );
}
void udp_connection::member::write( network_handle const & handle, char const * send_data )
{
    write( handle, std::string( send_data ) );
}
void udp_connection::member::write( network_handle const & handle, char const * send_data, size_t const & send_data_byte )
{
    try
    {
        udp::resolver resolver( _io_service );
        udp::resolver::query query( udp::v4( ),
                                    handle->ip_address,
                                    boost::lexical_cast<std::string>( handle->port ) );
        _udp_socket.send_to( asio::buffer( send_data, send_data_byte ),
                             resolver.resolve( query )->endpoint( ) );
        server_log( _remote_endpoint.address( ).to_string( ), _remote_endpoint.port( ),
                    "データを送信しました。" );
    }
    catch ( asio::error_code& error )
    {
        server_log( _remote_endpoint.address( ).to_string( ), _remote_endpoint.port( ),
                    "データを送れませんでした。: %s", error.message( ).c_str( ) );
        if ( _server.on_send_failed )_server.on_send_failed( );
    }
    if ( _server.on_sended )_server.on_sended( );
}
void udp_connection::member::_kill( )
{
    if ( !_is_update ) return;
    _is_update = false;
    _io_service.stop( );
    _update_io_service.join( );
}
void udp_connection::member::update( float delta_second )
{
    _client_manager.update( delta_second );
}
recursion_usable_mutex & udp_connection::member::get_mutex( )
{
    return _mutex;
}
void udp_connection::member::_read( )
{
    _udp_socket.async_receive_from( asio::buffer( _remote_buffer ),
                                    _remote_endpoint,
                                    [ this ] ( const asio::error_code& e, size_t bytes_transferred )
    {
        if ( e )
        {
            server_log( _remote_endpoint.address( ).to_string( ), _remote_endpoint.port( ),
                        "データを受け取れませんでした。: %s", e.message( ).c_str( ) );
            if ( _server.on_read_failed )_server.on_read_failed( );
        }
        else
        {
            server_log( _remote_endpoint.address( ).to_string( ), _remote_endpoint.port( ),
                        "データを受信しました。" );

            _on_received( bytes_transferred );

            std::fill_n( _remote_buffer.begin( ), bytes_transferred, 0 );

            // 再帰呼び出しですが、非同期なので大丈夫です。
            _read( );
        }
    } );
}
void udp_connection::member::_on_received( size_t bytes_transferred )
{
    // 受信したデータをJson形式として読み込みます。
    Json::Reader reader;
    Json::Value root;
    if ( reader.parse( _remote_buffer.data( ), root ) )
    {
        _client_manager.receive_entry_point( _remote_endpoint.address( ).to_string( ),
                                             _remote_endpoint.port( ),
                                             root );
    }
    else
    {
        server_log( _remote_endpoint.address( ).to_string( ), _remote_endpoint.port( ),
                    "データ形式を認識できませんでした。" );
        if ( _server.on_received_not_support_format )_server.on_received_not_support_format( _remote_buffer.data( ), bytes_transferred );
    }
}
}
