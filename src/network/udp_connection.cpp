﻿#include "udp_connection.h"
#include "udp_connection_member.h"
namespace network
{
udp_connection::udp_connection( )
{
    _m = new member( *this );
}
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
void udp_connection::write( network_handle const & handle, std::string const & send_data )
{
    _m->write( handle, send_data );
}
void udp_connection::write( network_handle const & handle, char const * send_data )
{
    _m->write( handle, send_data );
}
void udp_connection::write( network_handle const & handle, char const * send_data, size_t send_data_byte )
{
    _m->write( handle, send_data, send_data_byte );
}
void udp_connection::update( float delta_second )
{
    _m->update( delta_second );
}
utility::recursion_usable_mutex & udp_connection::get_mutex( )
{
    return _m->get_mutex( );
}
}
