#include "feed_manager.h"
#include <treelike/user_default.h>
using namespace cinder;
using namespace treelike;
namespace user
{
CREATE_CPP( feed_manager )
{
    CREATE( feed_manager );
}
bool feed_manager::init( )
{
    _random_handle = std::make_shared<cinder::Rand>( 2017 );
    for ( int i = 0; i < user_default::get_instans( )->get_root( )["number_of_feed"].asInt( ); ++i ) add_feed( );
    return true;
}
std::shared_ptr<feed> feed_manager::add_feed( )
{
    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );
    auto position = cinder::vec2( _random_handle->nextInt( ground_size * ground_scale ),
                                  _random_handle->nextInt( ground_size * ground_scale ) );
    auto feed = std::make_shared<user::feed>( );
    if ( feed && feed->init( position, _id++ ) );
    else feed.reset( );
    return add_child( feed );
}
void feed_manager::remove( int id )
{
    remove_child_by_tag( id );
}
}
