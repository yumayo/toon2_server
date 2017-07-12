#pragma once
#include "noticed_base.h"
#include "../synchronization_objects.h"
namespace user
{
namespace noticed
{
class ground : public noticed_base
{
    std::map<treelike::network::network_handle, std::vector<cell_data>> _prev_enemy_datas;
public:
    ground( receive_data_execute& execute );
public:
    void udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root ) override;
};
}
}
