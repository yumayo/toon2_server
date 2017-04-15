#include "noticed_base.h"
namespace network
{
namespace noticed
{
noticed_base::noticed_base( udp_connection& connection, receive_data_execute& clients )
    : _connection( connection )
    , _clients( clients )
{
}
}
}
