#pragma once
#include "noticed_base.h"
#include "cinder/Color.h"
namespace user
{
namespace noticed
{
// ���̃N���X���N���C�A���g���Ăё����邱�ƂŃz�X�g�Ƃ��Ĉێ��ł���悤�ɂȂ�܂��B
class close : public noticed_base
{
public:
    close( network::udp_connection& connection );
public:
    void receive_entry_point( network::network_handle handle, Json::Value root ) override;
};
}
}
