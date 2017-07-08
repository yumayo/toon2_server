#include "bullet_manager.h"
#include <treelike/action.hpp>
#include "default_scene.h"
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
std::shared_ptr<bullet> bullet_manager::add_bullet( cinder::vec2 position, cinder::vec2 direction, int user_id )
{
    auto bullet = std::make_shared<user::bullet>( );
    if ( bullet && bullet->init( position, direction, _id++ ) );
    else bullet.reset( );

    auto n = get_child_by_tag( user_id );
    if ( !n )
    {
        n = add_child( node::create( ) );
        n->set_tag( user_id );
    }

    return n->add_child( bullet );
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
