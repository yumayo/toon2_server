#include "network_factory.h"

network_handle network_factory::make( std::string const & ip_address, int const & port )
{
    auto ip_address_component = _ip_addresses.emplace( ip_address );
    auto port_component = _port.emplace( port );
    return network_handle( *ip_address_component.first, *port_component.first );
}
