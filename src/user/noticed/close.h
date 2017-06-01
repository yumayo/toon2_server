#pragma once
#include "noticed_base.h"
#include "cinder/Color.h"
namespace user
{
namespace noticed
{
// このクラスをクライアントが呼び続けることでホストとして維持できるようになります。
class close : public noticed_base
{
public:
    close( network::udp_connection& connection );
public:
    void receive_entry_point( network::network_handle handle, Json::Value root ) override;
};
}
}
