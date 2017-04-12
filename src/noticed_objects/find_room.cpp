#include "find_room.h"
find_room::find_room( connection_server & server )
    : noticed_base_object( server )
{
}
void find_room::receive_entry_point( network_handle const& handle, Json::Value const & data )
{
    if ( !_host )
    {
        _host = handle;
    }
    Json::Value root;
    root["NAME"] = "founded";
    root["DATA"]["is_host"] = ( ( **_host ) ) == ( *handle );
    root["DATA"]["ip_address"] = ( *_host )->ip_address; //( *_host )->ip_address 通信中アクセス違反1回。
    root["DATA"]["port"] = ( *_host )->port;
    _server.write( handle, root );
}
