#pragma once
#include "jsoncpp/json.h"
#include "../network_object.h"
#include "../udp_connection.h"
#include "../receive_data_execute.h"
namespace network
{
namespace noticed
{
class noticed_base
{
protected:
    receive_data_execute& _clients;
    udp_connection& _connection;
public:
    noticed_base( ) = delete;
    noticed_base( udp_connection& connection, receive_data_execute& clients );
    virtual ~noticed_base( ) {}
public:
    virtual void receive_entry_point( network_handle const& handle ) = 0;
};
}
}
