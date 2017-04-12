#pragma once
#include "network_object.h"
#include "jsoncpp/json.h"
#include <functional>
#include "cinder/gl/scoped.h"
#include "scoped_mutex.h"
class connection_server
{
    class member;
    member* _m;
public:
    connection_server( int const& port_number );
    ~connection_server( );
    void write( network_handle const& handle, Json::Value const& send_data );
    void update( float delta_second );
    std::mutex& get_mutex( );
public:
    // 別スレッドでの呼び出しなのでmutexを付けて変数を操作してください。
    std::function<void( char const*, size_t )> on_readed;
    // 別スレッドでの呼び出しなのでmutexを付けて変数を操作してください。
    std::function<void( )> on_read_failed;

    std::function<void( )> on_sended;
    std::function<void( )> on_send_failed;

    std::function<void( )> on_closed;
};