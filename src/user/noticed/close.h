#pragma once
#include "noticed_base.h"
#include "cinder/Color.h"
namespace user
{
namespace noticed
{
class close : public noticed_base
{
public:
    close( receive_data_execute& execute );
public:
    void udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
};
}
}
