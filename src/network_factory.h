#pragma once
#include <set>
#include "network_object.h"
// std::setがstd::shared_ptrの比較を行うとき、ポインタのアドレス同士で比較が行われます。
// アドレスは違くてもその中身は一緒ということがあるので、その中身での比較を行うようにします。
bool operator==( std::shared_ptr<network_object> const& left, std::shared_ptr<network_object> const& right );
bool operator<( std::shared_ptr<network_object> const& left, std::shared_ptr<network_object> const& right );
bool operator<=( std::shared_ptr<network_object> const& left, std::shared_ptr<network_object> const& right );

class network_factory
{
    std::set<std::shared_ptr<network_object>> _network_objects;
public:
    network_handle make( std::string const& ip_address, int const& port );
    network_handle make_with_timeout_restart( std::string const& ip_address, int const& port );
    void update( float delta_second );
};