#include "check_handle.h"
namespace user
{
namespace noticed
{
check_handle::check_handle( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void check_handle::udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root )
{
}
void check_handle::tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root )
{
    auto u_handle = _execute.user_handle_mgr( ).add_user_handle( handle.ip_address, handle.port, root["data"]["udp_port"].asInt( ) );

    Json::Value r;
    r["name"] = "id_received";
    r["data"]["id"] = u_handle->first;
    _execute.tcp( ).write( handle, Json::FastWriter( ).write( r ) );
}

}
}
