#pragma once
#include <list>
#include "network_object.h"
#include "udp_connection.h"

namespace network
{
class network_factory
{
    udp_connection& _server;
    std::list<std::shared_ptr<network_object>> _network_objects;
public:
    network_factory( udp_connection& server );
    network_handle make( std::string const& ip_address, int const& port );
    network_handle make_with_timeout_restart( std::string const& ip_address, int const& port );
    std::list<std::shared_ptr<network_object>>::iterator find_network_object( network_handle handle );
    std::list<std::shared_ptr<network_object>>::iterator find_network_object( std::shared_ptr<network_object> handle );
    void update( float delta_second );
};
}