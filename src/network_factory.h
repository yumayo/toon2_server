#pragma once
#include <set>
#include "network_object.h"
// std::set��std::shared_ptr�̔�r���s���Ƃ��A�|�C���^�̃A�h���X���m�Ŕ�r���s���܂��B
// �A�h���X�͈Ⴍ�Ă����̒��g�͈ꏏ�Ƃ������Ƃ�����̂ŁA���̒��g�ł̔�r���s���悤�ɂ��܂��B
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