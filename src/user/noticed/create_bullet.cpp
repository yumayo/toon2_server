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
        auto pos = vec2( data["position"][0].asFloat( ), data["position"][1].asFloat( ) );
        auto direction = vec2( data["direction"][0].asFloat( ), data["direction"][1].asFloat( ) );
        auto user_id = data["user_id"].asInt( );
        auto bullet = _execute.bullet_mgr( ).add_bullet( pos, direction, user_id );
        r["data"][index] = data;
        r["data"][index]["bullet_id"] = bullet->get_tag( );
        index++;
    }
    _execute.tcp( ).speech( Json::FastWriter( ).write( r ) );
}
}
}
