#include "bullet.h"
#include <treelike/action.hpp>
using namespace cinder;
using namespace treelike;
namespace user
{
bool bullet::init( cinder::vec2 position, cinder::vec2 direction, int bullet_id )
{
    set_schedule_update( );

    _direction = direction;
    set_position( position );
    set_tag( bullet_id );
    _time_remaining = 2.0F;

    using namespace action;
    run_action( sequence::create( delay::create( 2.0F ), remove_self::create( ) ) );

    return true;
}
void bullet::update( float delta )
{
    _position += _direction * 400.0F * delta;
    _time_remaining = std::max( _time_remaining - delta, 0.0F );
}
float const & bullet::get_radius( ) const
{
    return _radius;
}
cinder::vec2 const & bullet::get_direction( ) const
{
    return _direction;
}
float const & bullet::get_time_remaining( ) const
{
    return _time_remaining;
}
}
