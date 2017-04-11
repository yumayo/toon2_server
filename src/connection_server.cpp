#include "connection_server.h"
#include "connection_server_member.h"
connection_server::connection_server( )
{
    _m = new member( *this, 25565 );
}
connection_server::~connection_server( )
{
    delete _m;
}
void connection_server::write( network_handle const & handle, Json::Value const & send_data )
{
    _m->write( handle, send_data );
}
void connection_server::update( )
{
    _m->run( );
}
