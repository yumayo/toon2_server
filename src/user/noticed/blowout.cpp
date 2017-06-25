#include "blowout.h"
#include "find_room.h"
#include "check_handle.h"
#include "boost/lexical_cast.hpp"
#include "ground.h"
namespace user
{
namespace noticed
{
blowout::blowout( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void blowout::udp_receive_entry_point( network::network_handle handle, Json::Value const & root )
{
}
void blowout::tcp_receive_entry_point( network::client_handle handle, Json::Value const & root )
{
    auto check = std::dynamic_pointer_cast<check_handle>( _execute.find( "check_handle" ) );

    _execute.bullet_mgr( ).remove_child_by_tag( root["data"]["id"].asInt( ) );

    Json::Value r;
    r["name"] = "erase_bullet";
    r["data"]["id"] = root["data"]["id"].asInt( );
    _execute.tcp( ).speech( Json::FastWriter( ).write( r ) );
}
}
}
