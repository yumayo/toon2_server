#pragma once
#include "network/udp_connection.h"
#include "noticed.hpp"
namespace user
{
class receive_data_execute
{
    network::udp_connection& _connection;
    // 文字列から命令を実行するためのもの。
    std::map<std::string, std::shared_ptr<noticed::noticed_base>> _noticed_objects;
public:
    receive_data_execute( ) = delete;
    receive_data_execute( network::udp_connection& connection );
    void receive_entry_point( network::network_handle handle, Json::Value root );
};
}
