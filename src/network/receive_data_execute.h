#pragma once
#include "network_factory.h"

namespace network
{
namespace noticed
{
class noticed_base;
}
class receive_data_execute : public network_factory
{
    // �����񂩂疽�߂����s���邽�߂̂��́B
    std::map<std::string, std::shared_ptr<noticed::noticed_base>> _noticed_objects;
public:
    receive_data_execute( ) = delete;
    receive_data_execute( udp_connection& parent );
    void receive_entry_point( std::string const& ip_address, int const& port, Json::Value const& root );
};
}
