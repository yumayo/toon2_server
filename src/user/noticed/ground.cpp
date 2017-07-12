#include "ground.h"
#include "feed_captured.h"
#include "check_handle.h"
#include <cinder/Rand.h>
#include <treelike/user_default.h>
#include <treelike/utility.hpp>
#include <cinder/Rect.h>
#include <cinder/Vector.h>
#include <treelike/scene_manager.h>
#include <treelike/action.hpp>
using namespace cinder;
using namespace treelike;
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
        std::map<int, int> scores;
        auto& color_map = _execute.ground_color_mgr( ).get_ground_color_id( );
        for ( int y = 0; y < color_map.size( ); ++y )
        {
            for ( int x = 0; x < color_map[y].size( ); ++x )
            {
                for ( auto& handle : _execute.user_handle_mgr( ).get_user_handles( ) )
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
void ground::udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root )
{
    auto id = _execute.user_handle_mgr( ).find_id( handle );

    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );

    std::vector<cell_data> cell_datas;
    for ( auto& data : root["data"] )
    {
        cell_datas.push_back( { data["frame"].asInt( ), data["time"].asFloat( ), data["radius"].asFloat( ),
                              vec2( data["position"][0].asFloat( ), data["position"][1].asFloat( ) ) } );
    }
    auto& prev_cell_datas = _prev_enemy_datas[handle];
    // パケットロスがあったら
    if ( !prev_cell_datas.empty( ) && cell_datas.back( ).frame - 2 == prev_cell_datas.back( ).frame )
    {
        auto packet_loss_frame = ( cell_datas.back( ).frame - 1 ) - prev_cell_datas.back( ).frame;
        if ( cell_datas.size( ) < packet_loss_frame ) throw std::runtime_error( "ぱけろありすぎ" );
        auto& data = cell_datas[cell_datas.size( ) - packet_loss_frame];
        float packet_loss_time = data.time;
        int user_id = _execute.user_handle_mgr( ).find_id( handle );
        for ( int i = cell_datas.size( ) - packet_loss_frame; i < cell_datas.size( ); ++i )
        {
            _execute.ground_color_mgr( ).insert( cell_datas[i].time, cell_datas[i].position, cell_datas[i].radius, user_id );
        }
    }
    else
    {
        auto radius = cell_datas.back( ).radius / ground_scale;
        auto pixel = cell_datas.back( ).position / (float)ground_scale;
        Rectf rect( glm::floor( pixel - radius - 1.0F ), glm::ceil( pixel + radius ) );
        _execute.ground_color_mgr( ).paint_circle( cell_datas.back( ).time, rect, radius, id );
    }
    _prev_enemy_datas[handle] = cell_datas;
}
void ground::tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root )
{
}
}
}
