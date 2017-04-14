#include "find_room.h"
#include "string_utility.h"
namespace network
{
namespace noticed
{
find_room::find_room( udp_connection & server )
    : noticed_base( server )
{
}
void find_room::receive_entry_point( network_handle const& handle, Json::Value const & data )
{
    scoped_mutex mutex( _server.get_mutex( ) );

    if ( !_host )
    {
        _host = handle;
        server_log( _host->ip_address, _host->port,
                    "このオブジェクトがホストになりました。" );
    }
    Json::Value root;
    root["name"] = "founded";
    root["data"]["is_host"] = _host == handle;
    root["data"]["ip_address"] = _host->ip_address;
    root["data"]["port"] = _host->port;
    _server.write( handle, root );
}
}
}
