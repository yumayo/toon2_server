#include "bullet.h"
#include "action.hpp"
namespace user
{
CREATE_CPP( bullet, cinder::vec2 position, cinder::vec2 direction, int player_id )
{
    CREATE( bullet, position, direction, player_id );
}
bool bullet::init( cinder::vec2 position, cinder::vec2 direction, int player_id )
{
    set_schedule_update( );

    _direction = direction;
    set_position( position );
    set_tag( player_id );

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
}
