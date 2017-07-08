#pragma once
#include <treelike/network.hpp>
#include "bullet_manager.h"
#include "ground_color_manager.h"
#include "feed_manager.h"
#include "user_handle_manager.h"
namespace user
{
namespace noticed
{
class noticed_base;
}
class receive_data_execute
{
    treelike::network::tcp_server& _tcp_connection;
    treelike::network::udp_connection& _udp_connection;
    user::bullet_manager& _bullet_manager;
    user::ground_color_manager& _ground_color_manager;
    user::feed_manager& _feed_manager;
    user::user_handle_manager& _user_handle_manager;
    // ï∂éöóÒÇ©ÇÁñΩóﬂÇé¿çsÇ∑ÇÈÇΩÇﬂÇÃÇ‡ÇÃÅB
    std::map<std::string, std::shared_ptr<noticed::noticed_base>> _noticed_objects;
public:
    receive_data_execute( ) = delete;
    receive_data_execute( treelike::network::tcp_server& tcp_connection,
                          treelike::network::udp_connection& udp_connection,
                          user::bullet_manager& bullet_manager,
                          user::ground_color_manager& ground_color_manager,
                          user::feed_manager& feed_manager,
                          user::user_handle_manager& user_handle_manager );
    void udp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root );
    void tcp_receive_entry_point( treelike::network::network_handle handle, Json::Value const& root );
public:
    std::shared_ptr<noticed::noticed_base> find( std::string name );
    treelike::network::tcp_server& tcp( );
    treelike::network::udp_connection& udp( );
    user::bullet_manager& bullet_mgr( );
    user::ground_color_manager& ground_color_mgr( );
    user::feed_manager& feed_mgr( );
    user::user_handle_manager& user_handle_mgr( );
    void clear( int const& user_id );
};
}
