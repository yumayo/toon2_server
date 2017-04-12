#pragma once
#include "noticed_object/noticed_object.h"
#include "network_factory.h"
#include "write_on_destroyed.h"
#include "udp_connection.h"
namespace network
{
class client_manager
{
    udp_connection& _server;

    network_factory _network_handle_factory;

    // �����񂩂疽�߂����s���邽�߂̂��́B
    std::map<std::string, noticed_object*> _noticed_objects;
public:
    client_manager( udp_connection& parent );
    ~client_manager( );
    // �Ăяo�������֐���S�ēo�^���܂��B
    void regist_functions( );
    void receive_entry_point( std::string const& ip_address, int const& port, Json::Value const& root );
    void update( float delta_second );
};
}
