#pragma once
#include "noticed_base.h"
namespace user
{
namespace noticed
{
class feed_captured : public noticed_base
{
public:
    feed_captured( receive_data_execute& execute );
public:
    void udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
};
}
}
