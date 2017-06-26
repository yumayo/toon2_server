#include "default_scene.h"
#include "network.hpp"
#include "boost/lexical_cast.hpp"
#include "user_default.h"
using namespace cinder;
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

    auto tcp = network::tcp_server::create( boost::lexical_cast<std::string>( tcp_port ), maximum_clients );
    add_child( tcp );
    auto udp = network::udp_connection::create( udp_port );
    add_child( udp );
    auto bullet_mgr = bullet_manager::create( );
    add_child( bullet_mgr );
    auto ground_color_mgr = ground_color_manager::create( );
    ground_color_mgr->set_bullet_manager( bullet_mgr );
    add_child( ground_color_mgr );
    _receive_exe = std::make_unique<receive_data_execute>( *tcp, *udp, *bullet_mgr, *ground_color_mgr );

    tcp->on_readed = [ this ] ( network::client_handle const& handle, char const* data, size_t byte )
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
    tcp->on_client_disconnected = [ this ] ( network::client_handle const& handle )
    {
        Json::Value root;
        root["name"] = "close";
        _receive_exe->tcp_receive_entry_point( handle, root );
    };
    tcp->on_errored = [ this ] ( network::client_handle const& handle, asio::error_code const& )
    {
        Json::Value root;
        root["name"] = "close";
        _receive_exe->tcp_receive_entry_point( handle, root );
    };

    return true;
}
}