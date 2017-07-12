#include "create_bullet.h"
#include "find_room.h"
#include "check_handle.h"
#include "../bullet.h"
#include <treelike/user_default.h>
using namespace cinder;
namespace user
{
namespace noticed
{
create_bullet::create_bullet( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void create_bullet::udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const & root )
{
}
void create_bullet::tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const & root )
{
    int index = 0;
    Json::Value r;
    r["name"] = "create_bullet";
    for ( auto& data : root["data"] )
    {
        auto start_position = vec2( data["start_position"][0].asFloat( ), data["start_position"][1].asFloat( ) );
        auto end_position = vec2( data["end_position"][0].asFloat( ), data["end_position"][1].asFloat( ) );
        auto user_id = data["user_id"].asInt( );
        auto bullet_id = data["bullet_id"].asInt( );
        auto radius = data["radius"].asFloat( );
        auto bullet = _execute.bullet_mgr( ).add_bullet( user_id, bullet_id, radius, start_position, end_position );
        r["data"][index] = data;
        index++;
    }
    for ( auto& client : _execute.tcp( ).get_clients( ) )
    {
        if ( client == handle ) continue;
        _execute.tcp( ).write( client, Json::FastWriter( ).write( r ) );
    }
}
}
}
