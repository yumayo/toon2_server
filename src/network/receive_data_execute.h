#pragma once
#include "noticed/noticed_base.h"
#include "network_factory.h"
namespace network
{
class receive_data_execute : public network_factory
{
    // •¶š—ñ‚©‚ç–½—ß‚ğÀs‚·‚é‚½‚ß‚Ì‚à‚ÌB
    std::map<std::string, std::unique_ptr<noticed::noticed_base>> _noticed_objects;
public:
    receive_data_execute( ) = delete;
    receive_data_execute( udp_connection& parent );
    void receive_entry_point( std::string const& ip_address, int const& port, Json::Value const& root );
};
}
