#pragma once
#include "noticed_base.h"
namespace user
{
namespace noticed
{
class create_bullet : public noticed_base
{
public:
    create_bullet( receive_data_execute& execute );
public:
    void udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
};
}
}
