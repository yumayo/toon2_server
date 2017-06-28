#include "find_room.h"
#include "feed_captured.h"
#include "check_handle.h"
#include "user_default.h"
#include "utility.hpp"
#include "ground.h"
namespace user
{
namespace noticed
{
find_room::find_room( receive_data_execute& execute )
    : noticed_base( execute )
    , _random_device( 2017 )
{
}
void find_room::udp_receive_entry_point( network::network_handle handle, Json::Value const& root )
{
}
void find_room::tcp_receive_entry_point( network::client_handle handle, Json::Value const& root )
{
    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );

    int id = root["data"]["id"].asInt( );

    auto c = _execute.user_handle_mgr( ).find_client( id );
    if ( c.first )
    {
        c.second->second.root = root["data"];
        auto color = cinder::hsvToRgb( cinder::vec3( _random_device.nextFloat( ),
                                                     _random_device.nextFloat( 0.6F, 0.8F ),
                                                     _random_device.nextFloat( 0.7F, 0.8F ) ) );
        c.second->second.root["color"][0] = color.r;
        c.second->second.root["color"][1] = color.g;
        c.second->second.root["color"][2] = color.b;
    }

    // 適当な位置にスポーンさせます。
    auto spawn_position = cinder::ivec2( _random_device.nextInt( 0, ground_size * ground_scale ),
                                         _random_device.nextInt( 0, ground_size * ground_scale ) );

    // 全クライアントに通知。
    for ( auto& child : _execute.tcp( ).get_clients( ) )
    {
        // 接続してきた本人にはホストが見つかったというの情報を送ります。
        if ( handle == child )
        {
            // 接続してきたオブジェクト自身のデータを詰めます。
            Json::Value root;
            root["name"] = "founded";
            root["data"] = c.second->second.create_user_data( );
            root["data"]["position"][0] = spawn_position.x;
            root["data"]["position"][1] = spawn_position.y;
            root["data"]["ground_size"] = ground_size;
            root["data"]["ground_scale"] = ground_scale;

            // サーバーに接続中のオブジェクト全てのデータを詰めます。
            {
                int index = 0;
                for ( auto& user : _execute.user_handle_mgr( ).get_user_handles( ) )
                {
                    if ( user.first == id ) continue;
                    root["data"]["clients"][index] = user.second.create_user_data( );
                    index++;
                }
            }

            auto& feed_objects = _execute.feed_mgr( ).get_children( );
            auto const FEED_NUMBER = feed_objects.size( );
            root["data"]["feed_number"] = FEED_NUMBER;

            auto& color_map = _execute.ground_color_mgr( ).get_ground_color_id( );
            auto GROUND_SIZE = color_map.size( ); // マップは正方形です。
            root["data"]["ground_size"] = GROUND_SIZE;

            // ひとまず先にデータを送ります。
            _execute.tcp( ).write( child, Json::FastWriter( ).write( root ) );

            // エサの情報とグラウンドの情報を全て詰めます。
            struct header
            {
                char name[16];
                int byte;
            };
            struct feed_data
            {
                int tag;
                int x;
                int y;
            };
            
            {
                std::unique_ptr<unsigned char [ ]> feed_binary_data( new unsigned char [sizeof( header ) + sizeof( feed_data ) * FEED_NUMBER] );
                int index = 0;
                header* feed_header = new( feed_binary_data.get( ) + index ) header;
                std::memcpy( feed_header->name, "feed_data", sizeof( "feed_data" ) );
                feed_header->byte = sizeof( header ) + sizeof( feed_data ) * FEED_NUMBER;
                index += sizeof( header );

                for ( auto& feed : feed_objects )
                {
                    feed_data* f = new( feed_binary_data.get( ) + index ) feed_data;
                    f->tag = feed->get_tag( );
                    f->x = feed->get_position( ).x;
                    f->y = feed->get_position( ).y;
                    index += sizeof( feed_data );
                }
                _execute.tcp( ).write( child, (char*)feed_binary_data.get( ), index );
            }

            // グラウンドの状況を詰めます。
            {
                std::unique_ptr<unsigned char [ ]> ground_binary_data( new unsigned char[sizeof( header ) + sizeof( unsigned char ) * GROUND_SIZE * GROUND_SIZE] );
                int index = 0;
                header* feed_header = new( ground_binary_data.get( ) + index ) header;
                std::memcpy( feed_header->name, "ground_data", sizeof( "ground_data" ) );
                feed_header->byte = sizeof( header ) + sizeof( unsigned char ) * GROUND_SIZE * GROUND_SIZE;
                index += sizeof( header );

                for ( int y = 0; y < color_map.size( ); ++y )
                {
                    for ( int x = 0; x < color_map.size( ); ++x )
                    {
                        ground_binary_data[index] = color_map[x][y];
                        index += sizeof( unsigned char );
                    }
                }
                _execute.tcp( ).write( child, (char*)ground_binary_data.get( ), index );
            }
        }
        // それ以外の人には新しくクライアントが来たという情報を提供します。
        else
        {
            Json::Value root;
            root["name"] = "new_client";
            root["data"] = c.second->second.create_user_data( );
            root["data"]["position"][0] = spawn_position.x;
            root["data"]["position"][1] = spawn_position.y;
            _execute.tcp( ).write( child, Json::FastWriter( ).write( root ) );
        }
    }
}
}
}
