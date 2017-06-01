#pragma once
#include "noticed_base.h"
#include "cinder/Color.h"
namespace user
{
namespace noticed
{
class find_room : public noticed_base
{
    // Œ±“I‚É•”‰®‚Íˆê‚Â‚Æ‚µ‚Ü‚·B
    network::network_handle _host;
    std::map<network::network_handle, Json::Value> _client_data;
public:
    find_room( network::udp_connection& connection );
public:
    void receive_entry_point( network::network_handle handle, Json::Value root ) override;
};
}
}
