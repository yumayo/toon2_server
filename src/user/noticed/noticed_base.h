#pragma once
#include <jsoncpp/json.h>
#include <treelike/network/network_handle.h>
#include <treelike/network/udp_connection.h>
#include "../receive_data_execute.h"
namespace user
{
namespace noticed
{
class noticed_base
{
protected:
    receive_data_execute& _execute;
public:
    noticed_base( ) = delete;
    noticed_base( receive_data_execute& execute );
    virtual ~noticed_base( ) {}
public:
    virtual void udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) = 0;
    virtual void tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) = 0;
};
}
}
