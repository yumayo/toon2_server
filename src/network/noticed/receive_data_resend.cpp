#include "receive_data_resend.h"
#include "string_utility.h"
namespace network
{
namespace noticed
{
receive_data_resend::receive_data_resend( udp_connection & server )
    : noticed_base( server )
{
}
void receive_data_resend::receive_entry_point( network_handle const& handle, Json::Value const & data )
{
    scoped_mutex mutex( _server.get_mutex( ) );

    // そっくりそのままお返しします。
    _server.write( handle, data );
}
}
}
