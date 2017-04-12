#pragma once
#include "jsoncpp/json.h"
#include "../network_handle.h"
#include "../connection_server.h"
class noticed_base_object
{
protected:
    connection_server& _server;
public:
    noticed_base_object( connection_server& server );
    virtual ~noticed_base_object( ) {}
public:
    virtual void receive_entry_point( network_handle const& handle, Json::Value const & data ) = 0;
};