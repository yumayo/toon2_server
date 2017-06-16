#pragma once
#include "noticed_base.h"
#include "cinder/Rand.h"
namespace user
{
namespace noticed
{
class feed_captured : public noticed_base
{
    std::pair<int, cinder::ivec2> create_feed( );
    std::map<int, cinder::ivec2> _feed_objects;
    int _tag = 0;
    std::shared_ptr<cinder::Rand> _random_handle;
public:
    feed_captured( receive_data_execute& execute );
public:
    void udp_receive_entry_point( network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( network::client_handle handle, Json::Value const& root ) override;
public:
    std::map<int, cinder::ivec2> const& get_feed_objects( ) const;
};
}
}
