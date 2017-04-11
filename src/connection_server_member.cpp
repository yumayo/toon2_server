#include "connection_server_member.h"
#include "jsoncpp/json.h"
#include "string_utility.h"
connection_server::member::member( connection_server& parent, int const & port_num )
    : _parent( parent )
    , _udp_socket( _io_service, udp::endpoint( udp::v4( ), port_num ) )
    , _client_manager( parent )
{
    read( );
}
void connection_server::member::run( )
{
    _io_service.run( );
    _io_service.reset( );
}
void connection_server::member::write( network_handle const & handle, Json::Value const & send_data )
{
    Json::FastWriter writer;
    auto data = writer.write( send_data );
    try
    {
        udp::resolver resolver( _io_service );
        udp::resolver::query query( udp::v4( ),
                                    handle.ip_address,
                                    boost::lexical_cast<std::string>( handle.port ) );
        _udp_socket.send_to( asio::buffer( data.c_str( ), data.size( ) ),
                             resolver.resolve( query )->endpoint( ) );
    }
    catch ( asio::error_code& error )
    {
        log( "データを送れませんでした。: %s", error.message( ).c_str( ) );
    }
}
void connection_server::member::read( )
{
    _udp_socket.async_receive_from( asio::buffer( _remote_buffer ),
                                    _remote_endpoint,
                                    [ this ] ( const asio::error_code& e, size_t bytes_transferred )
    {
        if ( e )
        {
            log( "データを受け取れませんでした。: %s", e.message( ).c_str( ) );
        }
        else
        {
            log( "データを受信しました。" );

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

            std::fill_n( _remote_buffer.begin( ), bytes_transferred, 0 );

            // 再帰呼び出しですが、非同期なので大丈夫です。
            read( );
        }
    } );
}
