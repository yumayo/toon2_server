#pragma once
#include "noticed_base.h"
namespace user
{
namespace noticed
{
class player_on_captured : public noticed_base
{
public:
    player_on_captured( receive_data_execute& execute );
public:
    void udp_receive_entry_point( network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( network::client_handle handle, Json::Value const& root ) override;
};
}
}
