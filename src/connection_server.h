#pragma once
#include "network_handle.h"
#include "jsoncpp/json.h"
class connection_server
{
    class member;
    member* _m;
public:
    connection_server( );
    ~connection_server( );
    void write( network_handle const& handle, Json::Value const& send_data );
    void update( );
};