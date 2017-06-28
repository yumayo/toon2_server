#include "check_handle.h"
#include "boost/lexical_cast.hpp"
namespace user
{
namespace noticed
{
check_handle::check_handle( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void check_handle::udp_receive_entry_point( network::network_handle handle, Json::Value const& root )
{
}
void check_handle::tcp_receive_entry_point( network::client_handle handle, Json::Value const& root )
{
    auto u_handle = _execute.user_handle_mgr( ).add_user_handle( handle.ip_address, boost::lexical_cast<int>( handle.port ), root["data"]["udp_port"].asInt( ) );

    Json::Value r;
    r["name"] = "id_received";
    r["data"]["id"] = u_handle->first;
    _execute.tcp( ).write( handle, Json::FastWriter( ).write( r ) );
}

}
}
