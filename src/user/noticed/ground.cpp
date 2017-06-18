#include "ground.h"
#include "feed_captured.h"
#include "check_handle.h"
#include "cinder/Rand.h"
#include "user_default.h"
#include "utility.hpp"
using namespace cinder;
namespace user
{
namespace noticed
{
ground::ground( receive_data_execute& execute )
    : noticed_base( execute )
{
    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );

    _ground_color = std::vector<std::vector<int>>( ground_size, std::vector<int>( ground_size ) );
}
void ground::udp_receive_entry_point( network::network_handle handle, Json::Value const& root )
{
    auto check = std::dynamic_pointer_cast<check_handle>( _execute.find( "check_handle" ) );
    auto id = check->find_id( handle->ip_address, handle->port );

    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );

    auto radius = root["data"]["radius"].asFloat( ) / ground_scale;

    auto pixel = ivec2( root["data"]["position"][0].asFloat( ) / ground_scale,
                        root["data"]["position"][1].asFloat( ) / ground_scale );
    for ( int y = -radius; y <= radius; ++y )
    {
        for ( int x = -radius; x <= radius; ++x )
        {
            if ( radius < length( vec2( x, y ) ) ) continue;

            auto pos = glm::clamp( pixel + ivec2( x, y ), ivec2( 0 ), ivec2( ground_size - 1 ) );
            _ground_color[pos.x][pos.y] = id;
        }
    }
}
void ground::tcp_receive_entry_point( network::client_handle handle, Json::Value const& root )
{
}
std::vector<std::vector<int>>& ground::get_ground_color( )
{
    return _ground_color;
}
}
}
