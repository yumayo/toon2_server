#pragma once
#include "noticed_base_object.h"
class find_room : public noticed_base_object
{
    // �����I�ɕ����͈�Ƃ��܂��B
    network_handle _host;
public:
    find_room( connection_server& server );
public:
    void receive_entry_point( network_handle const& handle, Json::Value const& data ) override;
};