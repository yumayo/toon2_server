#include "find_room.h"
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
    if ( !_host )
    {
        _host = handle;
        utility::log_network( _host->ip_address, _host->port,
                              "このオブジェクトがホストになりました。" );
    }

    for ( auto& child : _connection.get_clients( ) )
    {
        if ( handle == child )
        {
            Json::Value root;
            root["name"] = "founded";
            root["data"]["is_host"] = handle == _host;
            root["data"]["ip_address"] = handle->ip_address;
            root["data"]["port"] = handle->port;
            int index = 0;
            for ( auto& c : _connection.get_clients( ) )
            {
                if ( handle == c ) continue;
                root["data"]["clients"][index]["ip_address"] = c->ip_address;
                root["data"]["clients"][index]["port"] = c->port;
            }
            _connection.write( child, root );
        }
        else
        {
            Json::Value root;
            root["name"] = "new_client";
            root["data"]["ip_address"] = handle->ip_address;
            root["data"]["port"] = handle->port;
            _connection.write( child, root );
        }
    }
}
}
}
