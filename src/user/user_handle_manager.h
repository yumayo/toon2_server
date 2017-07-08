#pragma once
#include <treelike/node.h>
#include "user_handle.h"
#include <treelike/network/network_handle.h>
namespace user
{
class user_handle_manager : public treelike::node
{
    std::map<int, bool> _id;
    std::map<int, user_handle> _user_handles;
public:
    CREATE_H( user_handle_manager, int const& maximum_clients );
    bool init( int const& maximum_clients );
public:
    static int INVALID_ID;
    std::map<int, user_handle> const& get_user_handles( ) const;
    std::pair<bool, std::map<int, user_handle>::iterator> find_client( int const& id );
    int find_id( treelike::network::network_handle handle );
    int find_tcp_port( treelike::network::network_handle handle );
    int find_udp_port( treelike::network::network_handle handle );
    std::map<int, user_handle>::iterator add_user_handle( std::string const& ip_address, int const& tcp_port, int const& udp_port );
    void clear( int user_id );
};
}