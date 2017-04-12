#pragma once
#include "network_handle.h"
#include <set>
#include "network_object.h"
class network_factory
{
    std::set<network_object> _network_objects;
public:
    network_handle make( std::string const& ip_address, int const& port );
    network_handle make_with_timeout_restart( std::string const& ip_address, int const& port );
    void update( float delta_second );
};