#pragma once
#include <string>
#include "network_object.h"
class network_handle
{
public:
    network_handle( std::string const& ip_address, int const& port );
    network_handle( network_object const& network_seed );
public:
    // 危険なコピーをします。強制的にconstを外すので。
    network_handle const& operator=( network_handle const& other ) const;
    network_handle const& operator=( network_object const& other ) const;
    bool operator==( network_handle const& other ) const;
    bool operator<( network_handle const& other ) const;
    bool operator<=( network_handle const& other ) const;
public: // 値はこのオブジェクトの作者のみ、書き換えることができます。
    std::string const& ip_address;
    int const& port;
};
