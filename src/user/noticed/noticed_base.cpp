#include "noticed_base.h"
namespace user
{
namespace noticed
{
noticed_base::noticed_base( network::udp_connection& connection )
    : _connection( connection )
{
}
}
}
