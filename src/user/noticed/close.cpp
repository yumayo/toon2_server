#include "close.h"
#include "find_room.h"
#include "check_handle.h"
#include "boost/lexical_cast.hpp"
#include "ground.h"
namespace user
{
namespace noticed
{
close::close( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void close::udp_receive_entry_point( network::network_handle handle, Json::Value const & root )
{
}
void close::tcp_receive_entry_point( network::client_handle handle, Json::Value const & root )
{
    auto check = std::dynamic_pointer_cast<check_handle>( _execute.find( "check_handle" ) );
    auto udp_port = check->find_udp_port( handle.ip_address, boost::lexical_cast<int>( handle.port ) );
    if ( udp_port != check_handle::INVALID_ID )
    {
        _execute.udp( ).destroy_client( std::make_shared<network::network_object>( handle.ip_address, udp_port ) );
    }
    auto target_id = check->find_id( handle.ip_address, boost::lexical_cast<int>( handle.port ) );
    check->destroy_connection_handle( target_id );

    auto find_r = std::dynamic_pointer_cast<find_room>( _execute.find( "find_room" ) );
    find_r->erase_client_data( target_id );

    Json::Value r;
    r["name"] = "close_client";
    r["data"]["ip_address"] = handle.ip_address;
    r["data"]["udp_port"] = udp_port;
    _execute.tcp( ).speech( Json::FastWriter( ).write( r ) );

    _execute.ground_color_mgr( ).clear_color_id( target_id );

    _execute.bullet_mgr( ).clear_bullet_id( target_id );
}
}
}
