#include "check_handle.h"
#include "boost/lexical_cast.hpp"
namespace user
{
namespace noticed
{
int check_handle::INVALID_ID = -1;
check_handle::check_handle( receive_data_execute& execute )
    : noticed_base( execute )
{
}
void check_handle::udp_receive_entry_point( network::network_handle handle, Json::Value const& root )
{
}
void check_handle::tcp_receive_entry_point( network::client_handle handle, Json::Value const& root )
{
    ++_id;
    _connection_handles[_id].ip_address = handle.ip_address;
    _connection_handles[_id].tcp_port = boost::lexical_cast<int>( handle.port );
    _connection_handles[_id].udp_port = root["data"]["udp_port"].asInt( );

    Json::Value r;
    r["name"] = "id_received";
    r["data"]["id"] = _id;
    _execute.tcp( ).write( handle, Json::FastWriter( ).write( r ) );
}
std::map<int, connection_handle> const & check_handle::get_connection_handles( ) const
{
    return _connection_handles;
}
int check_handle::find_id( std::string const & address, int const & port )
{
    for ( auto& h : _connection_handles )
    {
        if ( h.second.ip_address == address && 
             ( h.second.tcp_port == port || h.second.udp_port == port ) )
        {
            return h.first;
        }
    }
    return INVALID_ID;
}
int check_handle::find_tcp_port( std::string const & address, int const & udp_port )
{
    for ( auto& h : _connection_handles )
    {
        if ( h.second.ip_address == address && h.second.udp_port == udp_port )
        {
            return h.second.tcp_port;
        }
    }
    return INVALID_ID;
}
int check_handle::find_udp_port( std::string const & address, int const & tcp_port )
{
    for ( auto& h : _connection_handles )
    {
        if ( h.second.ip_address == address && h.second.tcp_port == tcp_port )
        {
            return h.second.udp_port;
        }
    }
    return INVALID_ID;
}
void check_handle::destroy_connection_handle( int id )
{
    _connection_handles.erase( id );
}
}
}
