#include "blowout.h"
#include "find_room.h"
#include "check_handle.h"
#include "ground.h"
namespace user
{
namespace noticed
{
blowout::blowout( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void blowout::udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const & root )
{
}
void blowout::tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const & root )
{
    _execute.bullet_mgr( ).remove( root["data"]["id"].asInt( ) );

    Json::Value r;
    r["name"] = "erase_bullet";
    r["data"]["id"] = root["data"]["id"].asInt( );
    r["data"]["user_id"] = root["data"]["user_id"].asInt( );
    _execute.tcp( ).speech( Json::FastWriter( ).write( r ) );
}
}
}
