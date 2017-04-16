#include "default_scene.h"
#include "network/udp_connection.h"
using namespace cinder;
namespace user
{
CREATE_CPP( default_scene )
{
    CREATE( default_scene );
}
bool default_scene::init( )
{
    auto connection = network::udp_connection::create( 25565 );
    _receive_exe = std::make_unique<receive_data_execute>( *connection );
    connection->on_received_json = [ this ] ( network::network_handle handle, Json::Value root )
    {
        _receive_exe->receive_entry_point( handle, root );
    };
    add_child( connection );
    return true;
}
}