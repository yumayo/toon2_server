#include "find_room.h"
#include "feed_captured.h"
#include "check_handle.h"
#include "user_default.h"
#include "utility.hpp"
#include "ground.h"
#include "../synchronization_objects.h"
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
            root["data"]["number_of_feed"] = FEED_NUMBER;

            auto& color_map = _execute.ground_color_mgr( ).get_ground_color_id( );
            auto GROUND_SIZE = color_map.size( ); // マップは正方形です。
            root["data"]["ground_size"] = GROUND_SIZE;

            auto& bullet_objects = _execute.bullet_mgr( ).get_children( );
            auto NUMBER_OF_BULLET = bullet_objects.size( );
            root["data"]["number_of_bullet"] = NUMBER_OF_BULLET;

            // ひとまず先にデータを送ります。
            _execute.tcp( ).write( child, Json::FastWriter( ).write( root ) );

            // フィールドに飛んでいるバレットを同期します。
            {
                std::unique_ptr<unsigned char [ ]> binary( new unsigned char[sizeof( header ) + sizeof( bullet_data ) * FEED_NUMBER] );
                int index = 0;
                header* feed_header = new( binary.get( ) + index ) header;
                std::memcpy( feed_header->name, "bullet_data", sizeof( "bullet_data" ) );
                feed_header->byte = sizeof( header ) + sizeof( bullet_data ) * NUMBER_OF_BULLET;
                index += sizeof( header );

                for ( auto& bullet_folder : bullet_objects )
                {
                    for ( auto& bullet_node : bullet_folder->get_children( ) )
                    {
                        auto bullet = std::dynamic_pointer_cast<user::bullet>( bullet_node );
                        bullet_data* b = new( binary.get( ) + index ) bullet_data;
                        b->position = bullet->get_position( );
                        b->direction = bullet->get_direction( );
                        b->user_id = bullet_folder->get_tag( );
                        b->id = bullet->get_tag( );
                        b->time_remaining = bullet->get_time_remaining( );
                        index += sizeof( bullet_data );
                    }
                }

                _execute.tcp( ).write( child, (char*)binary.get( ), index );
            }
            // エサの情報を詰めます。
            {
                std::unique_ptr<unsigned char [ ]> binary( new unsigned char[sizeof( header ) + sizeof( feed_data ) * FEED_NUMBER] );
                int index = 0;
                header* feed_header = new( binary.get( ) + index ) header;
                std::memcpy( feed_header->name, "feed_data", sizeof( "feed_data" ) );
                feed_header->byte = sizeof( header ) + sizeof( feed_data ) * FEED_NUMBER;
                index += sizeof( header );

                for ( auto& feed_node : feed_objects )
                {
                    feed_data* f = new( binary.get( ) + index ) feed_data;
                    f->id = feed_node->get_tag( );
                    f->position = feed_node->get_position( );
                    index += sizeof( feed_data );
                }
                _execute.tcp( ).write( child, (char*)binary.get( ), index );
            }
            // グラウンドの状況を詰めます。
            {
                std::unique_ptr<unsigned char [ ]> binary( new unsigned char[sizeof( header ) + sizeof( ground_data ) * GROUND_SIZE * GROUND_SIZE] );
                int index = 0;
                header* feed_header = new( binary.get( ) + index ) header;
                std::memcpy( feed_header->name, "ground_data", sizeof( "ground_data" ) );
                feed_header->byte = sizeof( header ) + sizeof( unsigned char ) * GROUND_SIZE * GROUND_SIZE;
                index += sizeof( header );

                for ( int y = 0; y < GROUND_SIZE; ++y )
                {
                    for ( int x = 0; x < GROUND_SIZE; ++x )
                    {
                        ground_data* data = new( binary.get( ) + index ) ground_data;
                        data->id = color_map[x][y];
                        index += sizeof( ground_data );
                    }
                }
                _execute.tcp( ).write( child, (char*)binary.get( ), index );
            }
            // 終わりという情報を送ります。
            {
                std::unique_ptr<unsigned char [ ]> binary( new unsigned char[sizeof( header )] );
                int index = 0;
                header* feed_header = new( binary.get( ) + index ) header;
                std::memcpy( feed_header->name, "finished", sizeof( "finished" ) );
                feed_header->byte = sizeof( header ) + sizeof( unsigned char ) * GROUND_SIZE * GROUND_SIZE;
                index += sizeof( header );

                _execute.tcp( ).write( child, (char*)binary.get( ), index );
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
