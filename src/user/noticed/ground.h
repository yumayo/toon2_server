#pragma once
#include "noticed_base.h"
namespace user
{
namespace noticed
{
class ground : public noticed_base
{
    std::vector<std::vector<unsigned char>> _ground_color_id;
public:
    ground( receive_data_execute& execute );
public:
    void udp_receive_entry_point( network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( network::client_handle handle, Json::Value const& root ) override;
public:
    std::vector<std::vector<unsigned char>>& get_ground_color_id( );
    void clear_color_id( int const& id );
};
}
}
