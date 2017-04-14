#pragma once
#include "jsoncpp/json.h"
#include "../network_object.h"
#include "../udp_connection.h"
namespace network
{
namespace noticed
{
class noticed_base
{
protected:
    udp_connection& _server;
public:
    noticed_base( ) = delete;
    noticed_base( udp_connection& server );
    virtual ~noticed_base( ) {}
public:
    virtual void receive_entry_point( network_handle const& handle, Json::Value const & data ) = 0;
};
}
}
