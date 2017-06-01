#include "close.h"
namespace user
{
namespace noticed
{
close::close( network::udp_connection& connection )
    : noticed_base( connection )
{
}
void close::receive_entry_point( network::network_handle handle, Json::Value root )
{
    _connection.destroy_client( handle );
}
}
}
