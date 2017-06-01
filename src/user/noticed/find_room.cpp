﻿#include "find_room.h"
#include "string_utility.h"
namespace user
{
namespace noticed
{
find_room::find_room( network::udp_connection& connection )
    : noticed_base( connection )
{
}
void find_room::receive_entry_point( network::network_handle handle, Json::Value root )
{
    _client_data[handle] = root["data"];
    _client_data[handle]["color"] = ( _client_data.size( ) & 0x1 ) == 0x0 ? "purple" : "green";

    if ( !_host )
    {
        _host = handle;
        utility::log_network( _host->ip_address, _host->port,
                              "このオブジェクトがホストになりました。" );
    }

    // 全クライアントに通知。
    for ( auto& child : _connection.get_clients( ) )
    {
        // 接続してきた本人にはホストが見つかったというの情報を送ります。
        if ( handle == child )
        {
            // 接続してきたオブジェクト自身のデータを詰めます。
            Json::Value root;
            root["name"] = "founded";
            root["data"]["is_host"] = handle == _host;
            root["data"]["ip_address"] = handle->ip_address;
            root["data"]["port"] = handle->port;
            root["data"]["select_skin_name"] = _client_data[handle]["select_skin_name"].asString( );
            root["data"]["color"] = _client_data[handle]["color"].asString( );

            // サーバーに接続中のオブジェクト全てのデータを詰めます。
            int index = 0;
            for ( auto& c : _connection.get_clients( ) )
            {
                if ( handle == c ) continue;
                root["data"]["clients"][index]["ip_address"] = c->ip_address;
                root["data"]["clients"][index]["port"] = c->port;
                root["data"]["clients"][index]["select_skin_name"] = _client_data[c]["select_skin_name"].asString( );
                root["data"]["clients"][index]["color"] = _client_data[c]["color"].asString( );
                index++;
            }
            _connection.write( child, root );
        }
        // それ以外の人には新しくクライアントが来たという情報を提供します。
        else
        {
            Json::Value root;
            root["name"] = "new_client";
            root["data"]["ip_address"] = handle->ip_address;
            root["data"]["port"] = handle->port;
            root["data"]["select_skin_name"] = _client_data[handle]["select_skin_name"].asString( );
            root["data"]["color"] = _client_data[handle]["color"].asString( );
            _connection.write( child, root );
        }
    }
}
}
}
