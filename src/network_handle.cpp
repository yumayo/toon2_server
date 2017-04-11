#include "network_handle.h"
namespace network
{
network_handle::network_handle( std::string const & ip_address, std::string const & port )
    : ip_address( ip_address )
    , port( port )
{
}
bool network_handle::operator==( network_handle const & other ) const
{
    return 
        this->_name == other._name &&
        this->ip_address == other.ip_address &&
        this->port == other.ip_address;
}
void network_handle::set_name( std::string const & value )
{
    _name = value;
}
std::string const & network_handle::get_name( )
{
    return _name;
}
}
