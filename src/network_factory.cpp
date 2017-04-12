#include "network_factory.h"
#include <algorithm>
network_handle network_factory::make( std::string const & ip_address, int const & port )
{
    auto network_object_component = _network_objects.emplace( ip_address, port );
    return network_handle( *network_object_component.first );
}
network_handle network_factory::make_with_timeout_restart( std::string const & ip_address, int const & port )
{
    auto network_object_component = _network_objects.emplace( ip_address, port );
    network_object_component.first->timeout_restart( );
    return network_handle( *network_object_component.first );
}
void network_factory::update( float delta_second )
{
    auto remove_itr = std::remove_if( std::begin( _network_objects ), std::end( _network_objects ),
                                      [ delta_second ] ( network_object const& child ) -> bool
    {
        child.update( delta_second );
        return child.is_destroy( );
    } );
    _network_objects.erase( remove_itr, std::end( _network_objects ) );
}
