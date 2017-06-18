#pragma once
#include "noticed_base.h"
#include "../connection_handle.h"
namespace user
{
namespace noticed
{
// このクラスにユーザーのIDを保存しておきます。
class check_handle : public noticed_base
{
    std::map<int, bool> _id;
    std::map<int, connection_handle> _connection_handles;
public:
    check_handle( receive_data_execute& execute );
    static int INVALID_ID;
public:
    void udp_receive_entry_point( network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( network::client_handle handle, Json::Value const& root ) override;
public:
    std::map<int, connection_handle> const& get_connection_handles( ) const;
    int find_id( std::string const& address, int const& port );
    int find_tcp_port( std::string const& address, int const& udp_port );
    int find_udp_port( std::string const& address, int const& tcp_port );
    void destroy_connection_handle( int id );
};
}
}
