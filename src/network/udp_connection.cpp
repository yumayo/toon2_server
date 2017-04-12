#include "udp_connection.h"
#include "udp_connection_member.h"
namespace network
{
udp_connection::udp_connection( int const& port_number )
{
    _m = new member( *this, port_number );
}
udp_connection::~udp_connection( )
{
    delete _m;
}
void udp_connection::write( network_handle const & handle, Json::Value const & send_data )
{
    _m->write( handle, send_data );
}
void udp_connection::update( float delta_second )
{
    _m->update( delta_second );
}

std::mutex & udp_connection::get_mutex( )
{
    return _m->get_mutex( );
}
}
