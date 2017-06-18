#include "check_handle.h"
#include "boost/lexical_cast.hpp"
namespace user
{
namespace noticed
{
int check_handle::INVALID_ID = 0;
check_handle::check_handle( receive_data_execute& execute )
    : noticed_base( execute )
{
    _id[INVALID_ID] = true;
    for ( int i = 1; i < 255; ++i )
    {
        _id[i] = false;
    }
}
void check_handle::udp_receive_entry_point( network::network_handle handle, Json::Value const& root )
{
}
void check_handle::tcp_receive_entry_point( network::client_handle handle, Json::Value const& root )
{
    int no_use_id = INVALID_ID;
    for ( auto& id : _id )
    {
        if ( !id.second )
        {
            id.second = true;
            no_use_id = id.first;
            break;
        }
    }

    // tcp_serverの最大人数が255人と設定しているので、ここが呼ばれることはありません。
    if ( no_use_id == INVALID_ID ) return;

    _connection_handles[no_use_id].ip_address = handle.ip_address;
    _connection_handles[no_use_id].tcp_port = boost::lexical_cast<int>( handle.port );
    _connection_handles[no_use_id].udp_port = root["data"]["udp_port"].asInt( );

    Json::Value r;
    r["name"] = "id_received";
    r["data"]["id"] = no_use_id;
    _execute.tcp( ).write( handle, Json::FastWriter( ).write( r ) );
}
std::map<int, connection_handle> const & check_handle::get_connection_handles( ) const
{
    return _connection_handles;
}
connection_handle check_handle::find_client( int const & id )
{
    auto handle = _connection_handles.find( id );
    if ( handle != _connection_handles.end( ) )
    {
        return handle->second;
    }
    return connection_handle( );
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
    _id[id] = false;
}
}
}
