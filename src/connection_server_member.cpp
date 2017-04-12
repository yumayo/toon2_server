#include "connection_server_member.h"
#include "jsoncpp/json.h"
#include "string_utility.h"
connection_server::member::member( connection_server& parent, int const & port_num )
    : _parent( parent )
    , _port_number( port_num )
    , _udp_socket( _io_service, udp::endpoint( udp::v4( ), port_num ) )
    , _client_manager( parent )
{
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
connection_server::member::~member( )
{
    _kill( );
}
void connection_server::member::write( network_handle const & handle, Json::Value const & send_data )
{
    try
    {
        udp::resolver resolver( _io_service );
        udp::resolver::query query( udp::v4( ),
                                    handle.lock( )->ip_address,
                                    boost::lexical_cast<std::string>( handle.lock( )->port ) );
        Json::FastWriter writer;
        auto data = writer.write( send_data );
        _udp_socket.send_to( asio::buffer( data.c_str( ), data.size( ) ),
                             resolver.resolve( query )->endpoint( ) );
    }
    catch ( asio::error_code& error )
    {
        log( "データを送れませんでした。: %s", error.message( ).c_str( ) );
        if ( _parent.on_send_failed )_parent.on_send_failed( );
    }
    if ( _parent.on_sended )_parent.on_sended( );
}
void connection_server::member::_kill( )
{
    if ( !_is_update ) return;
    _is_update = false;
    _io_service.stop( );
    _update_io_service.join( );
    if ( _parent.on_closed )_parent.on_closed( );
}
void connection_server::member::update( float delta_second )
{
    _client_manager.update( delta_second );
}
void connection_server::member::_read( )
{
    _udp_socket.async_receive_from( asio::buffer( _remote_buffer ),
                                    _remote_endpoint,
                                    [ this ] ( const asio::error_code& e, size_t bytes_transferred )
    {
        if ( e )
        {
            log( "データを受け取れませんでした。: %s", e.message( ).c_str( ) );
            if ( _parent.on_read_failed )_parent.on_read_failed( );
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

void connection_server::member::_on_received( size_t bytes_transferred )
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

    if ( _parent.on_readed )_parent.on_readed( _remote_buffer.data( ), bytes_transferred );
}
