#include "network_factory.h"
#include <algorithm>
bool operator==( std::shared_ptr<network_object> const & left, std::shared_ptr<network_object> const & right )
{
    return ( *left.get( ) ) == ( *right.get( ) );
}
bool operator<( std::shared_ptr<network_object> const & left, std::shared_ptr<network_object> const & right )
{
    return ( *left.get( ) ) < ( *right.get( ) );
}
bool operator<=( std::shared_ptr<network_object> const & left, std::shared_ptr<network_object> const & right )
{
    return ( *left.get( ) ) <= ( *right.get( ) );
}
network_handle network_factory::make( std::string const & ip_address, int const & port )
{
    auto network_object_component = _network_objects.emplace( std::make_shared<network_object>( ip_address, port ) );
    return *network_object_component.first;
}
network_handle network_factory::make_with_timeout_restart( std::string const & ip_address, int const & port )
{
    auto network_object_component = _network_objects.emplace( std::make_shared<network_object>( ip_address, port ) );
    ( *network_object_component.first )->timeout_restart( );
    return *network_object_component.first;
}
void network_factory::update( float delta_second )
{
    // std::remove_ifがstd::shared_ptr<T> const& operator=に対応していないのでゴリ押しで。
    for ( auto itr = std::begin( _network_objects ), end = std::end( _network_objects );
          itr != end;
          itr++ )
    {
        ( *itr )->update( delta_second );
        if ( ( *itr )->is_destroy( ) )
        {
            itr = _network_objects.erase( itr );
            if ( itr == end )
                break;
        }
    }
}

