#pragma once
#include <string>
namespace user
{
struct connection_handle
{
    std::string ip_address;
    int tcp_port = 0;
    int udp_port = 0;
};
}