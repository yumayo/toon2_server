#pragma once
#include "noticed_base.h"
#include "cinder/Color.h"
namespace network
{
namespace noticed
{
class find_room : public noticed_base
{
    // Œ±“I‚É•”‰®‚Íˆê‚Â‚Æ‚µ‚Ü‚·B
    network_handle _host;
public:
    find_room( udp_connection& connection, receive_data_execute& clients );
public:
    void receive_entry_point( network_handle const& handle ) override;
};
}
}
