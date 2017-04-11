#include "network_handle.h"
network_handle::network_handle( std::string const & ip_address, int const & port )
    : ip_address( ip_address )
    , port( port )
{
}
network_handle const& network_handle::operator=( network_handle const& other ) const
{
    const_cast<std::string&>( this->ip_address ) = other.ip_address;
    const_cast<int&>( this->port ) = other.port;
    return *const_cast<network_handle*>( this );
}
bool network_handle::operator==( network_handle const & other ) const
{
    return
        this->ip_address == other.ip_address &&
        this->port == other.port;
}
bool network_handle::operator<( network_handle const & other ) const
{
    return
        this->ip_address < other.ip_address &&
        this->port < other.port;
}
bool network_handle::operator<=( network_handle const & other ) const
{
    return
        this->ip_address <= other.ip_address &&
        this->port <= other.port;
}
