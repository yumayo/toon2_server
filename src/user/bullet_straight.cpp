#include "bullet_straight.h"
#include <treelike/action.hpp>
using namespace cinder;
using namespace treelike;
namespace user
{
CREATE_CPP( bullet_straight, int bullet_id, float radius, cinder::vec2 start_position, cinder::vec2 end_position )
{
    CREATE( bullet_straight, bullet_id, radius, start_position, end_position );
}
bool bullet_straight::init( int bullet_id, float radius, cinder::vec2 start_position, cinder::vec2 end_position )
{
    bullet::init( bullet_id, radius, start_position );
    _time_remaining = 2.0F;
    run_action( action::sequence::create( action::move_to::create( _time_remaining, end_position ), 
                                          action::remove_self::create( ) ) );
    return true;
}
void bullet_straight::update( float delta )
{
    _time_remaining = std::max( _time_remaining - delta, 0.0F );
}
float bullet_straight::get_time_remaining( ) const
{
    return _time_remaining;
}
}
