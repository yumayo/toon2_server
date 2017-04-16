#pragma once
#include "noticed_base.h"
namespace user
{
namespace noticed
{
class receive_data_resend : public noticed_base
{
public:
    receive_data_resend( network::udp_connection& connection );
public:
    void receive_entry_point( network::network_handle handle, Json::Value root ) override;
};
}
}
