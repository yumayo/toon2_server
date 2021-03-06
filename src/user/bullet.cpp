#include "bullet.h"
#include <treelike/action.hpp>
using namespace cinder;
using namespace treelike;
namespace user
{
bool bullet::init( int bullet_id, float radius, cinder::vec2 start_position )
{
    set_schedule_update( );

    set_tag( bullet_id );
    set_position( start_position );
    _start_position = start_position;
    _radius = radius;

    return true;
}
cinder::vec2 bullet::get_start_position( )
{
    return _start_position;
}
float bullet::get_radius( ) const
{
    return _radius;
}
}
