#include "find_room.h"
#include "feed_captured.h"
#include "check_handle.h"
#include "cinder/Rand.h"
#include "user_default.h"
#include "utility.hpp"
namespace user
{
namespace noticed
{
find_room::find_room( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void find_room::udp_receive_entry_point( network::network_handle handle, Json::Value const& root )
{
}
void find_room::tcp_receive_entry_point( network::client_handle handle, Json::Value const& root )
{
    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );

    auto check = std::dynamic_pointer_cast<check_handle>( _execute.find( "check_handle" ) );

    int id = root["id"].asInt( );

    auto itr = check->get_connection_handles( ).find( id );
    if ( itr != check->get_connection_handles( ).end( ) )
    {
        _client_data[id] = root["data"]; // スキンや他のデータを詰める。
        _client_data[id]["ip_address"] = itr->second.ip_address;
        _client_data[id]["udp_port"] = itr->second.udp_port;
        _client_data[id]["tcp_port"] = itr->second.tcp_port;
        _client_data[id]["color"] = ( _client_data.size( ) & 0x1 ) == 0x0 ? "purple" : "green";

        cinder::app::console( ) << "全てのクライアントデータ" << std::endl;
        for ( auto& client : _client_data )
        {
            utility::log( "ID[%d]", client.first );
            cinder::app::console( ) << client.second;
        }
        cinder::app::console( ) << std::endl;
    }

    auto feed_mgr = std::dynamic_pointer_cast<feed_captured>( _execute.find( "feed_captured" ) );

    // 全クライアントに通知。
    for ( auto& child : _execute.tcp( ).get_clients( ) )
    {
        // 接続してきた本人にはホストが見つかったというの情報を送ります。
        if ( handle == child )
        {
            // 接続してきたオブジェクト自身のデータを詰めます。
            Json::Value root;
            root["name"] = "founded";
            root["data"] = _client_data[id];

            // 適当な位置にスポーンさせます。
            cinder::Rand rand( cinder::app::getElapsedSeconds( ) );
            root["data"]["position"][0] = rand.nextInt( 0, ground_size );
            root["data"]["position"][1] = rand.nextInt( 0, ground_size );

            // グラウンドのサイズを相手にあげます。
            root["data"]["ground_size"] = ground_size;

            // エサの情報を全て詰めます。
            {
                int index = 0;
                for ( auto& feed : feed_mgr->get_feed_objects( ) )
                {
                    root["data"]["feeds"][index]["tag"] = feed.first;
                    root["data"]["feeds"][index]["position"][0] = feed.second.x;
                    root["data"]["feeds"][index]["position"][1] = feed.second.y;
                    index++;
                }
            }
            // サーバーに接続中のオブジェクト全てのデータを詰めます。
            {
                int index = 0;
                for ( auto& c : _client_data )
                {
                    if ( c.first == id ) continue;
                    root["data"]["clients"][index] = c.second;
                    index++;
                }
            }
            _execute.tcp( ).write( child, Json::FastWriter( ).write( root ) );
        }
        // それ以外の人には新しくクライアントが来たという情報を提供します。
        else
        {
            Json::Value root;
            root["name"] = "new_client";
            root["data"] = _client_data[id];
            _execute.tcp( ).write( child, Json::FastWriter( ).write( root ) );
        }
    }
}
void find_room::erase_client_data( int id )
{
    _client_data.erase( id );
}
}
}
