#pragma once
#include <string>
#include "use_destroy_object.h"
#include "user_pointer.hpp"
class network_object : public use_destroy_object
{
    // mutableはconst関数の中で値を書き換えたい場合に付けられる修飾子です。
    // http://soundengine.jp/wordpress/tips/tutorial/329/

    float mutable _second = 0.0F;
    float const _timeout_second = 5.0F;
public:
    network_object( ) = delete;
    network_object( std::string ip_address, int port );
    void update( float delta_second ) const;
    void timeout_restart( ) const;
    network_object const& operator=( network_object const& other ) const;
    bool operator==( network_object const& other ) const;
    bool operator<( network_object const& other ) const;
    bool operator<=( network_object const& other ) const;
public:
    std::string const ip_address;
    int const port;
};
using network_handle = softptr<network_object>;