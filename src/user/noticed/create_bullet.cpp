#include "create_bullet.h"
#include "find_room.h"
#include "check_handle.h"
#include "boost/lexical_cast.hpp"
#include "../bullet.h"
#include "user_default.h"
using namespace cinder;
namespace user
{
namespace noticed
{
create_bullet::create_bullet( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void create_bullet::udp_receive_entry_point( network::network_handle handle, Json::Value const & root )
{
}
void create_bullet::tcp_receive_entry_point( network::client_handle handle, Json::Value const & root )
{
    auto pos = vec2( root["data"]["position"][0].asFloat( ), root["data"]["position"][1].asFloat( ) );
    auto direction = vec2( root["data"]["direction"][0].asFloat( ), root["data"]["direction"][1].asFloat( ) );
    auto id = _execute.user_handle_mgr( ).find_id( handle );
    auto bullet = _execute.bullet_mgr( ).add_bullet( pos, direction, id );
    
    Json::Value r;
    r = root;
    r["data"]["tag"] = bullet->get_tag( );
    _execute.tcp( ).speech( Json::FastWriter( ).write( r ) );
}
}
}
