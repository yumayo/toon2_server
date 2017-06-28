#include "feed.h"
namespace user
{
bool feed::init( cinder::vec2 position, int id )
{
    set_position( position );
    set_tag( id );
    return true;
}
}
