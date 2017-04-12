#include "connection_server.h"
#include "connection_server_member.h"
connection_server::connection_server( int const& port_number )
{
    _m = new member( *this, port_number );
}
connection_server::~connection_server( )
{
    delete _m;
}
void connection_server::write( network_handle const & handle, Json::Value const & send_data )
{
    _m->write( handle, send_data );
}
void connection_server::update( float delta_second )
{
    _m->update( delta_second );
}

std::mutex & connection_server::get_mutex( )
{
    return _m->get_mutex( );
}
