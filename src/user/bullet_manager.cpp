#include "bullet_manager.h"
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
    if ( bullet && bullet->init( position, direction, user_id, _id++ ) );
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
        for ( auto& c : folder->get_children( ) )
        {
            if ( c->get_tag( ) == bullet_id ) c->remove_from_parent( );
        }
    }
}
void bullet_manager::clear( int user_id )
{
    for ( auto& folder : get_children( ) )
    {
        if ( folder->get_tag( ) == user_id ) folder->remove_from_parent( );
    }
}
}
