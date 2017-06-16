#pragma once
#include "network.hpp"
namespace user
{
namespace noticed
{
class noticed_base;
}
class receive_data_execute
{
    network::tcp_server& _tcp_connection;
    network::udp_connection& _udp_connection;
    // ï∂éöóÒÇ©ÇÁñΩóﬂÇé¿çsÇ∑ÇÈÇΩÇﬂÇÃÇ‡ÇÃÅB
    std::map<std::string, std::shared_ptr<noticed::noticed_base>> _noticed_objects;
public:
    receive_data_execute( ) = delete;
    receive_data_execute( network::tcp_server& tcp_connection, network::udp_connection& udp_connection );
    void udp_receive_entry_point( network::network_handle handle, Json::Value const& root );
    void tcp_receive_entry_point( network::client_handle handle, Json::Value const& root );
public:
    std::shared_ptr<noticed::noticed_base> find( std::string name );
    network::tcp_server& tcp( );
    network::udp_connection& udp( );
};
}
