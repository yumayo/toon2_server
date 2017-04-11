#include "network_handle.h"
network_handle::network_handle( std::string const & ip_address, int const & port )
    : ip_address( ip_address )
    , port( port )
{
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
