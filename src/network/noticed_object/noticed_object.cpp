#include "noticed_object.h"
namespace network
{
noticed_object::noticed_object( udp_connection & server )
    : _server( server )
{
}
}
