#pragma once
#include "cinder/Noncopyable.h"
#include <mutex>
#include "cinder/gl/scoped.h"
// cinder/gl/scoped.h を参考にしました。

namespace network
{
// インスタンス化するだけでそのスコープ内のみブロッキングします。
class scoped_mutex : cinder::Noncopyable
{
    std::mutex& _mutex;
public:
    scoped_mutex( ) = delete;
    scoped_mutex( std::mutex& server_mutex );
    ~scoped_mutex( );
};
}
