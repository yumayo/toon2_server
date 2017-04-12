#pragma once
#include "jsoncpp/json.h"
#include "../network_object.h"
#include "../udp_connection.h"
namespace network
{
class noticed_object
{
protected:
    udp_connection& _server;
public:
    noticed_object( udp_connection& server );
    virtual ~noticed_object( ) {}
public:
    virtual void receive_entry_point( network_handle const& handle, Json::Value const & data ) = 0;
};
}
