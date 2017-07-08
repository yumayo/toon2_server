#include "default_scene.h"
#include <treelike/network.hpp>
#include <treelike/user_default.h>
using namespace cinder;
using namespace treelike;
namespace user
{
CREATE_CPP( default_scene )
{
    CREATE( default_scene );
}
bool default_scene::init( )
{
    int udp_port = user_default::get_instans( )->get_root( )["udp_port"].asInt( );
    int tcp_port = user_default::get_instans( )->get_root( )["tcp_port"].asInt( );
    int maximum_clients = user_default::get_instans( )->get_root( )["maximum_clients"].asInt( );

    auto tcp = add_child( network::tcp_server::create( tcp_port, maximum_clients ) );
    auto udp = add_child( network::udp_connection::create( udp_port ) );
    auto bullet_manager = add_child( bullet_manager::create( ) );
    auto ground_color_manager = add_child( ground_color_manager::create( ) );
    ground_color_manager->set_bullet_manager( bullet_manager );
    auto feed_manager = add_child( feed_manager::create( ) );
    auto user_handle_manager = add_child( user_handle_manager::create( maximum_clients ) );
    _receive_exe = std::make_unique<receive_data_execute>( *tcp,
                                                           *udp,
                                                           *bullet_manager,
                                                           *ground_color_manager,
                                                           *feed_manager,
                                                           *user_handle_manager );

    tcp->on_readed = [ this ] ( network::network_handle const& handle, char const* data, size_t byte )
    {
        Json::Value root;
        if ( Json::Reader( ).parse( std::string( data, byte ), root ) )
        {
            _receive_exe->tcp_receive_entry_point( handle, root );
        }
    };
    udp->on_received_json = [ this ] ( network::network_handle handle, Json::Value root )
    {
        _receive_exe->udp_receive_entry_point( handle, root );
    };
    tcp->on_client_disconnected = [ this ] ( network::network_handle const& handle )
    {
        Json::Value root;
        root["name"] = "close";
        _receive_exe->tcp_receive_entry_point( handle, root );
    };
    tcp->on_errored = [ this ] ( network::network_handle const& handle, boost::system::error_code const& )
    {
        Json::Value root;
        root["name"] = "close";
        _receive_exe->tcp_receive_entry_point( handle, root );
    };

    return true;
}
receive_data_execute & default_scene::execute( )
{
    return *_receive_exe.get( );
}
}