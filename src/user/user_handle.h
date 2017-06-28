#pragma once
#include <string>
#include "jsoncpp/json.h"
namespace user
{
class user_handle
{
public:
    user_handle( std::string const& ip_address, int const& tcp_port, int const& udp_port );
    Json::Value create_user_data( ) const;
public:
    std::string const ip_address;
    int const tcp_port = 0;
    int const udp_port = 0;
    Json::Value root;
};
}