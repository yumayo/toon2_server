#include "noticed_base.h"
namespace network
{
namespace noticed
{
noticed_base::noticed_base( udp_connection & server )
    : _server( server )
{
}
}
}
