#include "network_object.h"
#include "cinder/CinderMath.h"
#include "string_utility.h"
namespace network
{
network_object::network_object( std::string const & ip_address, int const & port, Json::Value const & user_data )
    : ip_address( ip_address )
    , port( port )
    , user_data( user_data )
{
}
network_object::~network_object( )
{
    utility::log_network( ip_address, port,
                          "タイムアウトになりました。このオブジェクトは削除されました。" );
}
void network_object::update( float delta_second ) const
{
    _second = cinder::clamp( _second + delta_second, 0.0F, _timeout_second );
    if ( _second == _timeout_second )
    {
        destroy( );
    }
}
void network_object::timeout_restart( ) const
{
    _second = 0.0F;
}
network_object const& network_object::operator=( network_object const & other ) const
{
    this->_is_live = other._is_live;
    this->_second = other._second;
    const_cast<float&>( this->_timeout_second ) = other._timeout_second;
    const_cast<std::string&>( this->ip_address ) = other.ip_address;
    const_cast<int&>( this->port ) = other.port;
    const_cast<Json::Value&>( this->user_data ) = other.user_data;
    return *this;
}
bool network_object::operator==( network_object const & other ) const
{
    return
        this->ip_address == other.ip_address &&
        this->port == other.port;
}
}
