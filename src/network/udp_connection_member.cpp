#include "udp_connection_member.h"
#include "jsoncpp/json.h"
#include "string_utility.h"
namespace network
{
udp_connection::member::member( udp_connection& server, int const & port_num )
    : _server( server )
    , _port_number( port_num )
    , _udp_socket( _io_service, udp::endpoint( udp::v4( ), port_num ) )
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
udp_connection::member::~member( )
{
    _kill( );
}
void udp_connection::member::write( network_handle const & handle, Json::Value const & send_data )
{
    try
    {
        udp::resolver resolver( _io_service );
        udp::resolver::query query( udp::v4( ),
                                    handle->ip_address,
                                    boost::lexical_cast<std::string>( handle->port ) );
        Json::FastWriter writer;
        auto data = writer.write( send_data );
        _udp_socket.send_to( asio::buffer( data.c_str( ), data.size( ) ),
                             resolver.resolve( query )->endpoint( ) );
    }
    catch ( asio::error_code& error )
    {
        log( "データを送れませんでした。: %s", error.message( ).c_str( ) );
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
    if ( _server.on_closed )_server.on_closed( );
}
void udp_connection::member::update( float delta_second )
{
    _client_manager.update( delta_second );
}
std::mutex & udp_connection::member::get_mutex( )
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
            log( "データを受け取れませんでした。: %s", e.message( ).c_str( ) );
            if ( _server.on_read_failed )_server.on_read_failed( );
        }
        else
        {
            log( "データを受信しました。" );

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
        log( "データ形式を認識できませんでした。" );
    }

    if ( _server.on_readed )_server.on_readed( _remote_buffer.data( ), bytes_transferred );
}
}
