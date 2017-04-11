#include "connection_receiver.h"
#include "connection_receiver_member.h"
connection_receiver::connection_receiver( )
{
    _m = new member( 25565 );
}
connection_receiver::~connection_receiver( )
{
    delete _m;
}
void connection_receiver::update( )
{
    _m->run( );
}
