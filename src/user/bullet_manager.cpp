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
void bullet_manager::clear_bullet_id( int id )
{
    for ( auto& c : get_children( ) )
    {
        remove_child_by_tag( id );
    }
}
}
