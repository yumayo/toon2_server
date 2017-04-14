#pragma once
#include <string>
#include "use_destroy_object.h"
#include "user_pointer.hpp"
namespace network
{
class network_object : public use_destroy_object
{
    // mutable��const�֐��̒��Œl���������������ꍇ�ɕt������C���q�ł��B
    // http://soundengine.jp/wordpress/tips/tutorial/329/

    float mutable _second = 0.0F;
    float const _timeout_second = 60.0F;
public:
    network_object( ) = delete;
    network_object( std::string ip_address, int port );
    ~network_object( );
    void update( float delta_second ) const;
    void timeout_restart( ) const;
    network_object const& operator=( network_object const& other ) const;
    bool operator==( network_object const& other ) const;
public:
    std::string const ip_address;
    int const port;
};
using network_handle = softptr<network_object>;
}
