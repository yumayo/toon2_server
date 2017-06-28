#include "user_handle.h"
namespace user
{
user_handle::user_handle( std::string const & ip_address, int const & tcp_port, int const & udp_port )
    : ip_address( ip_address )
    , tcp_port( tcp_port )
    , udp_port( udp_port )
{
}
Json::Value user_handle::create_user_data( ) const
{
    Json::Value r = root;
    r["ip_address"] = ip_address;
    r["tcp_port"] = tcp_port;
    r["udp_port"] = udp_port;
    return r;
}
}
