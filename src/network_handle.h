#pragma once
#include <string>
class network_handle
{
public:
    network_handle( std::string const& ip_address, int const& port );
public:
    // 危険なコピーをします。強制的にconstを外すので。
    network_handle const& operator=( network_handle const& other ) const;
    bool operator==( network_handle const& other ) const;
    bool operator<( network_handle const& other ) const;
    bool operator<=( network_handle const& other ) const;
public: // 値は network_factory のみが書き換えられます。
    std::string const& ip_address;
    int const& port;
};
