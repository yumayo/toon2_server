#pragma once
#include "jsoncpp/json.h"
#include "network/network_object.h"
#include "network/udp_connection.h"
namespace user
{
namespace noticed
{
class noticed_base
{
protected:
    network::udp_connection& _connection;
public:
    noticed_base( ) = delete;
    noticed_base( network::udp_connection& connection );
    virtual ~noticed_base( ) {}
public:
    virtual void receive_entry_point( network::network_handle handle, Json::Value root ) = 0;
};
}
}
