#include "ground_color_manager.h"
#include "user_default.h"
#include "bullet_manager.h"
#include "bullet.h"
namespace user
{
CREATE_CPP( ground_color_manager )
{
    CREATE( ground_color_manager );
}
bool ground_color_manager::init( )
{
    set_schedule_update( );
    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );
    _ground_color_id = std::vector<std::vector<unsigned char>>( ground_size, std::vector<unsigned char>( ground_size ) );
    return true;
}
void ground_color_manager::set_bullet_manager( std::weak_ptr<node> bullet_manager )
{
    _bullet_manager = bullet_manager;
}
void ground_color_manager::update( float delta )
{
    auto bullet_manager = std::dynamic_pointer_cast<user::bullet_manager>( _bullet_manager.lock( ) );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );
    for ( auto const& c : bullet_manager->get_children( ) )
    {
        if ( auto const& bullet = std::dynamic_pointer_cast<user::bullet>( c ) )
        {
            auto radius = bullet->get_radius( ) / (float)ground_scale;
            auto pixel = cinder::vec2( bullet->get_position( ) / (float)ground_scale );

            cinder::Rectf rect( glm::floor( pixel - radius - 1.0F ), glm::ceil( pixel + radius ) );

            paint_circle( rect, bullet->get_radius( ), bullet->get_tag( ) );
        }
    }
}
std::vector<std::vector<unsigned char>>& ground_color_manager::get_ground_color_id( )
{
    return _ground_color_id;
}
void ground_color_manager::clear_color_id( int const & id )
{
    for ( int y = 0; y < _ground_color_id.size( ); ++y )
    {
        for ( int x = 0; x < _ground_color_id[y].size( ); ++x )
        {
            auto& pixel = _ground_color_id[x][y];
            if ( pixel == id )
            {
                pixel = 0;
            }
        }
    }
}
void ground_color_manager::paint_circle( cinder::Rectf rect, float radius, int id )
{
    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );

    for ( int y = rect.y1; y <= rect.y2; ++y )
    {
        for ( int x = rect.x1; x <= rect.x2; ++x )
        {
            if ( radius < glm::length( cinder::vec2( x, y ) - rect.getCenter( ) ) ) continue;

            auto pos = glm::clamp( cinder::ivec2( x, y ), cinder::ivec2( 0 ), cinder::ivec2( ground_size - 1 ) );
            _ground_color_id[pos.x][pos.y] = id;
        }
    }
}
}
