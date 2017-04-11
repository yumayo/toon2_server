#pragma once
#include "jsoncpp/json.h"
#include "../network_handle.h"
class noticed_base_object
{
public:
    noticed_base_object( ) {}
    virtual ~noticed_base_object( ) {}
public:
    virtual void receive_entry_point( network_handle& receive_info, Json::Value const & data ) = 0;
};