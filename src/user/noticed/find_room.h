#pragma once
#include "noticed_base.h"
namespace user
{
namespace noticed
{
class find_room : public noticed_base
{
    std::map<int, Json::Value> _client_data;
    int _tag = 0;
public:
    find_room( receive_data_execute& execute );
public:
    void udp_receive_entry_point( network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( network::client_handle handle, Json::Value const& root ) override;
public:
    void erase_client_data( int id );
};
}
}
