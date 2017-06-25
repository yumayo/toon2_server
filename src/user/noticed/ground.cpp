#include "ground.h"
#include "feed_captured.h"
#include "check_handle.h"
#include "cinder/Rand.h"
#include "user_default.h"
#include "utility.hpp"
#include "cinder/Rect.h"
#include "cinder/Vector.h"
#include "scene_manager.h"
#include "action.hpp"
#include "boost/lexical_cast.hpp"
using namespace cinder;
namespace user
{
namespace noticed
{
ground::ground( receive_data_execute& execute )
    : noticed_base( execute )
{
    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );

    auto dont_destroy_node = scene_manager::get_instans( )->get_dont_destroy_node( ).lock( );

    auto player_checker = node::create( );
    player_checker->set_name( "player_checker" );
    player_checker->run_action( action::repeat_forever::create( action::sequence::create( action::delay::create( 1.0f ), action::call_func::create(
        [ this ]
    {
        auto check = std::dynamic_pointer_cast<check_handle>( _execute.find( "check_handle" ) );
        std::map<int, int> scores;
        auto& color_map = _execute.ground_color_mgr( ).get_ground_color_id( );
        for ( int y = 0; y < color_map.size( ); ++y )
        {
            for ( int x = 0; x < color_map[y].size( ); ++x )
            {
                for ( auto& handle : check->get_connection_handles( ) )
                {
                    if ( color_map[x][y] == handle.first )
                    {
                        scores[handle.first] += 1;
                    }
                }
            }
        }
        // multimapで自動ソートしてもらう。
        std::multimap<int, std::map<int, int>::iterator> scoremap;
        for ( auto itr = scores.begin( ); itr != scores.end( ); ++itr )
        {
            scoremap.insert( std::make_pair( itr->second, itr ) );
        }
        Json::Value r;
        r["name"] = "ranking";
        int index = 0;
        for ( auto itr = scoremap.rbegin( ); itr != scoremap.rend( ); ++itr )
        {
            r["data"][index]["id"] = itr->second->first;
            r["data"][index]["score"] = itr->first;
            index++;
        }
        _execute.tcp( ).speech( Json::FastWriter( ).write( r ) );
    } ) ) ) );
    dont_destroy_node->add_child( player_checker );
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

    _execute.ground_color_mgr( ).paint_circle( rect, radius, id );
}
void ground::tcp_receive_entry_point( network::client_handle handle, Json::Value const& root )
{
}
}
}
