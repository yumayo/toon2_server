#pragma once
#include <list>
#include "network_object.h"
#include "udp_connection.h"
#include "jsoncpp/json.h"
namespace network
{
class network_factory
{
protected:
    udp_connection& _server;
    std::list<std::shared_ptr<network_object>> _network_objects;
public:
    network_factory( ) = delete;
    network_factory( udp_connection& server );
    virtual ~network_factory( ) { }
    network_handle regist( std::string const& ip_address, int const& port, Json::Value const& user_data );
    std::list<std::shared_ptr<network_object>>::iterator find_network_object( network_handle handle );
    std::list<std::shared_ptr<network_object>>::iterator find_network_object( std::shared_ptr<network_object> handle );
    std::list<std::shared_ptr<network_object>> const& get_children( );
    void update( float delta_second );
};
}