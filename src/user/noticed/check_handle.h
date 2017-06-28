#pragma once
#include "noticed_base.h"
namespace user
{
namespace noticed
{
// このクラスにユーザーのIDを保存しておきます。
class check_handle : public noticed_base
{
public:
    check_handle( receive_data_execute& execute );
public:
    void udp_receive_entry_point( network::network_handle handle, Json::Value const& root ) override;
    void tcp_receive_entry_point( network::client_handle handle, Json::Value const& root ) override;
};
}
}
