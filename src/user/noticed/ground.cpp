#include "ground.h"
#include "feed_captured.h"
#include "check_handle.h"
#include "cinder/Rand.h"
#include "user_default.h"
#include "utility.hpp"
#include "cinder/Rect.h"
#include "cinder/Vector.h"
using namespace cinder;
namespace user
{
namespace noticed
{
ground::ground( receive_data_execute& execute )
    : noticed_base( execute )
{
    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );

    _ground_color_id = std::vector<std::vector<unsigned char>>( ground_size, std::vector<unsigned char>( ground_size ) );
}
void ground::udp_receive_entry_point( network::network_handle handle, Json::Value const& root )
{
    auto check = std::dynamic_pointer_cast<check_handle>( _execute.find( "check_handle" ) );
    auto id = check->find_id( handle->ip_address, handle->port );

    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );

    auto radius = root["data"]["radius"].asFloat( ) / ground_scale;

    auto pixel = vec2( root["data"]["position"][0].asFloat( ) / ground_scale,
                       root["data"]["position"][1].asFloat( ) / ground_scale );

    Rectf rect( glm::floor( pixel - radius - 1.0F ), glm::ceil( pixel + radius ) );

    for ( int y = rect.y1; y <= rect.y2; ++y )
    {
        for ( int x = rect.x1; x <= rect.x2; ++x )
        {
            if ( radius < length( vec2( x, y ) - rect.getCenter( ) ) ) continue;

            auto pos = glm::clamp( ivec2( x, y ), ivec2( 0 ), ivec2( ground_size - 1 ) );
            _ground_color_id[pos.x][pos.y] = id;
        }
    }
}
void ground::tcp_receive_entry_point( network::client_handle handle, Json::Value const& root )
{
}
std::vector<std::vector<unsigned char>>& ground::get_ground_color_id( )
{
    return _ground_color_id;
}
}
}
