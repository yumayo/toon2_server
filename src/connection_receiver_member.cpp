#include "connection_receiver_member.h"
connection_receiver::member::member( int const& port_num )
    : _udp_socket( _io_service, udp::endpoint( udp::v4( ), port_num ) )
    , _update_log( "connection_receiver.log" )
{
    read( );
}
void connection_receiver::member::read( )
{
    _udp_socket.async_receive_from( asio::buffer( _reciving_buffer ),
                                    _reciving_endpoint,
                                    [ this ] ( const asio::error_code& e, size_t bytes_transferred )
    {
        if ( e )
        {
            log( "データを受け取れませんでした。: %s", e.message( ).c_str( ) );
        }
        else
        {
            log( "通信相手の情報: %s, %d",
                 _reciving_endpoint.address( ).to_string( ).c_str( ),
                 _reciving_endpoint.port( ) );
            log( "受け取ったデータ: %d byte", bytes_transferred );
            log_data( _reciving_buffer.data( ), bytes_transferred );
            std::fill_n( _reciving_buffer.begin( ), bytes_transferred, 0 );
            read( );
        }
    } );
}
void connection_receiver::member::run( )
{
    _io_service.reset( );
    auto ran_point = _io_service.run( );
    _update_log += format( u8"[%s] %dつの io_service が終了。\n",
                           cinder::app::getSystemTimeNamed( ).c_str( ),
                           ran_point );
}
