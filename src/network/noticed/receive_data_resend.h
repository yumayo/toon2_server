#pragma once
#include "noticed_base.h"
namespace network
{
namespace noticed
{
class receive_data_resend : public noticed_base
{
public:
    receive_data_resend( udp_connection& server );
public:
    void receive_entry_point( network_handle const& handle, Json::Value const& data ) override;
};
}
}
