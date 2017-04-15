#include "find_room.h"
#include "string_utility.h"
namespace network
{
namespace noticed
{
find_room::find_room( udp_connection& connection, receive_data_execute& clients )
    : noticed_base( connection, clients )
{
}
void find_room::receive_entry_point( network_handle const& handle )
{
    utility::scoped_mutex mutex( _connection.get_mutex( ) );

    if ( !_host )
    {
        _host = handle;
        utility::log_network( _host->ip_address, _host->port,
                              "このオブジェクトがホストになりました。" );
    }

    for ( auto& child : _clients.get_children( ) )
    {
        if ( handle == child )
        {
            Json::Value root;
            root["name"] = "founded";
            root["data"]["is_host"] = handle == _host;
            root["data"]["ip_address"] = handle->ip_address;
            root["data"]["port"] = handle->port;
            int index = 0;
            for ( auto& c : _clients.get_children( ) )
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
            root["data"]["is_host"] = handle == _host;
            root["data"]["ip_address"] = handle->ip_address;
            _connection.write( child, root );
        }
    }
}
}
}
