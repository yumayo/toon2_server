#pragma once
#include "network_handle.h"
#include <set>
class network_factory
{
    std::set<std::string> _ip_addresses;
    std::set<int> _port;
public:
    network_handle make( std::string const& ip_address, int const& port );
};