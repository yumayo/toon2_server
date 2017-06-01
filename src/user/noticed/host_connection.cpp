#include "host_connection.h"
namespace user
{
namespace noticed
{
host_connection::host_connection( network::udp_connection& connection )
    : noticed_base( connection )
{
}
void host_connection::receive_entry_point( network::network_handle handle, Json::Value root )
{
    // nothing: 呼び続けるダミーデータなので。
}
}
}
