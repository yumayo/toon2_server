#include "bullet_manager.h"
#include <treelike/action.hpp>
#include "default_scene.h"
#include "bullet_straight.h"
using namespace cinder;
using namespace treelike;
namespace user
{
CREATE_CPP( bullet_manager )
{
    CREATE( bullet_manager );
}
bool bullet_manager::init( )
{
    return true;
}
std::shared_ptr<bullet_straight> bullet_manager::add_bullet( int user_id, int bullet_id, float radius, cinder::vec2 start_position, cinder::vec2 end_position )
{
    auto folder = get_child_by_tag( user_id );
    if ( !folder )
    {
        folder = add_child( node::create( ) );
        folder->set_tag( user_id );
    }
    return folder->add_child( bullet_straight::create( bullet_id, radius, start_position, end_position ) );
}
void bullet_manager::remove( int bullet_id )
{
    for ( auto& folder : get_children( ) )
    {
        folder->remove_child_by_tag( bullet_id );
    }
}
void bullet_manager::clear( int user_id )
{
    remove_child_by_tag( user_id );
}
}
