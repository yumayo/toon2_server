#include "close.h"
#include "find_room.h"
#include "check_handle.h"
#include "boost/lexical_cast.hpp"
#include "ground.h"
namespace user
{
namespace noticed
{
close::close( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void close::udp_receive_entry_point( network::network_handle handle, Json::Value const & root )
{
}
void close::tcp_receive_entry_point( network::client_handle handle, Json::Value const & root )
{
    Json::Value r;
    r["name"] = "close_client";
    r["data"]["ip_address"] = handle.ip_address;
    r["data"]["udp_port"] = _execute.user_handle_mgr( ).find_udp_port( handle );
    _execute.tcp( ).speech( Json::FastWriter( ).write( r ) );

    _execute.clear( _execute.user_handle_mgr( ).find_id( handle ) );
}
}
}
