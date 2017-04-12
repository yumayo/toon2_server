#include "scoped_mutex.h"
namespace network
{
scoped_mutex::scoped_mutex( std::mutex& server_mutex )
    : _mutex( server_mutex )
{
    _mutex.lock( );
}
scoped_mutex::~scoped_mutex( )
{
    _mutex.unlock( );
}
}
