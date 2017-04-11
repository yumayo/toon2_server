#pragma once
#include <string>
namespace network
{
class network_handle
{
public:
    network_handle( std::string const& ip_address, std::string const& port );
public:
    bool operator==( network_handle const& other ) const;
public: // 値は tcp_server のみが書き換えられます。
    std::string const& ip_address;
    std::string const& port;

private:
    std::string _name;
public:
    void set_name( std::string const& value );
    std::string const& get_name( );
};
}
