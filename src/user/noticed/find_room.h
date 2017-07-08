#pragma once
#include "noticed_base.h"
#include "cinder/Rand.h"
namespace user
{
namespace noticed
{
class find_room : public noticed_base
{
    cinder::Rand _random_device;
public:
    find_room( receive_data_execute& execute );
public:
    void udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
};
}
}
