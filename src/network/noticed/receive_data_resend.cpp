#include "receive_data_resend.h"
#include "string_utility.h"
namespace network
{
namespace noticed
{
receive_data_resend::receive_data_resend( udp_connection& connection, receive_data_execute& clients )
    : noticed_base( connection, clients )
{
}
void receive_data_resend::receive_entry_point( network_handle const& handle )
{
    utility::scoped_mutex mutex( _connection.get_mutex( ) );

    // そっくりそのままお返しします。
    _connection.write( handle, handle->user_data );
}
}
}
