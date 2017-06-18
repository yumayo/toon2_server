#include "default_scene.h"
#include "network.hpp"
#include "boost/lexical_cast.hpp"
using namespace cinder;
namespace user
{
CREATE_CPP( default_scene )
{
    CREATE( default_scene );
}
bool default_scene::init( )
{
    auto tcp = network::tcp_server::create( "25564", 255 );
    add_child( tcp );
    auto udp = network::udp_connection::create( 25565 );
    add_child( udp );
    _receive_exe = std::make_unique<receive_data_execute>( *tcp, *udp );

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