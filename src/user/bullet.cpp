#include "bullet.h"
#include "action.hpp"
namespace user
{
bool bullet::init( cinder::vec2 position, cinder::vec2 direction, int user_id, int bullet_id )
{
    set_schedule_update( );

    _direction = direction;
    set_position( position );
    set_tag( bullet_id );
    set_user_id( user_id );

    using namespace action;
    run_action( sequence::create( delay::create( 3.0F ), remove_self::create( ) ) );

    return true;
}
void bullet::update( float delta )
{
    _position += _direction * 400.0F * delta;
}
float const & bullet::get_radius( ) const
{
    return _radius;
}
void bullet::set_user_id( int value )
{
    user_id = value;
}
int const & bullet::set_user_id( ) const
{
    return user_id;
}
}
