#include "receive_data_resend.h"
#include "string_utility.h"
namespace user
{
namespace noticed
{
receive_data_resend::receive_data_resend( network::udp_connection& connection )
    : noticed_base( connection )
{
}
void receive_data_resend::receive_entry_point( network::network_handle handle, Json::Value root )
{
    // そっくりそのままお返しします。
    _connection.write( handle, root );
}
}
}
