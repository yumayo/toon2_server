#pragma once
#include "noticed_object.h"
namespace network
{
class find_room : public noticed_object
{
    // �����I�ɕ����͈�Ƃ��܂��B
    network_handle _host;
public:
    find_room( udp_connection& server );
public:
    void receive_entry_point( network_handle const& handle, Json::Value const& data ) override;
};
}
