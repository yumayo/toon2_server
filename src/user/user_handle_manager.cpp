#include "user_handle_manager.h"
#include "user_default.h"
#include "boost/lexical_cast.hpp"
namespace user
{
int user_handle_manager::INVALID_ID = 0;
CREATE_CPP( user_handle_manager, int const& maximum_clients )
{
    CREATE( user_handle_manager, maximum_clients );
}
bool user_handle_manager::init( int const& maximum_clients )
{
    _id[INVALID_ID] = true;
    for ( int i = 1; i < maximum_clients; ++i ) _id[i] = false;
    return true;
}
std::map<int, user_handle> const & user_handle_manager::get_user_handles( ) const
{
    return _user_handles;
}
std::pair<bool, std::map<int, user_handle>::iterator> user_handle_manager::find_client( int const & id )
{
    auto itr = _user_handles.find( id );
    return std::make_pair( itr != _user_handles.end( ), itr );
}
int user_handle_manager::find_id( network::client_handle handle )
{
    for ( auto& h : _user_handles )
        if ( h.second.ip_address == handle.ip_address && 
            ( h.second.tcp_port == boost::lexical_cast<int>( handle.port ) || h.second.udp_port == boost::lexical_cast<int>( handle.port ) ) )
            return h.first;
    return INVALID_ID;
}
int user_handle_manager::find_id( network::network_handle handle )
{
    for ( auto& h : _user_handles )
        if ( h.second.ip_address == handle->ip_address &&
            ( h.second.tcp_port == handle->port || h.second.udp_port == handle->port ) )
            return h.first;
    return INVALID_ID;
}
int user_handle_manager::find_tcp_port( network::network_handle handle )
{
    for ( auto& h : _user_handles )
        if ( h.second.ip_address == handle->ip_address && h.second.udp_port == handle->port )
            return h.second.tcp_port;
    return INVALID_ID;
}
int user_handle_manager::find_udp_port( network::client_handle handle )
{
    for ( auto& h : _user_handles )
        if ( h.second.ip_address == handle.ip_address && h.second.tcp_port == boost::lexical_cast<int>( handle.port ) )
            return h.second.udp_port;
    return INVALID_ID;
}
std::map<int, user_handle>::iterator user_handle_manager::add_user_handle( std::string const & ip_address, int const & tcp_port, int const & udp_port )
{
    int void_id = INVALID_ID;
    for ( auto& id : _id )
    {
        if ( !id.second )
        {
            id.second = true;
            void_id = id.first;
            break;
        }
    }
    return  _user_handles.insert( std::make_pair( void_id, user_handle( ip_address, tcp_port, udp_port ) ) ).first;
}
void user_handle_manager::clear( int user_id )
{
    _user_handles.erase( user_id );
    _id[user_id] = false;
}
}
