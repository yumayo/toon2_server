#include "ground_color_manager.h"
#include <treelike/user_default.h>
#include "bullet_manager.h"
#include "bullet.h"
using namespace cinder;
using namespace treelike;
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
void ground_color_manager::set_bullet_manager( softptr<treelike::node> bullet_manager )
{
    _bullet_manager = bullet_manager;
}
void ground_color_manager::update( float delta )
{
    if ( _is_inserted )
    {
        for ( int i = _min_insert_iterator; i < _past_paint_datas.size( ); ++i )
        {
            paint_circle( _past_paint_datas[i].time,
                          Rectf( _past_paint_datas[i].position - _past_paint_datas[i].radius,
                                 _past_paint_datas[i].position + _past_paint_datas[i].radius ),
                          _past_paint_datas[i].radius,
                          _past_paint_datas[i].user_id );
        }
        _is_inserted = false;
        _min_insert_iterator = 0;
    }

    auto bullet_manager = std::dynamic_pointer_cast<user::bullet_manager>( _bullet_manager.lock( ) );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );
    for ( auto const& folder : bullet_manager->get_children( ) )
    {
        for ( auto const& bullet_node : folder->get_children( ) )
        {
            if ( auto const& bullet = std::dynamic_pointer_cast<user::bullet>( bullet_node ) )
            {
                auto radius = bullet->get_radius( ) / (float)ground_scale;
                auto pixel = cinder::vec2( bullet->get_position( ) / (float)ground_scale );

                cinder::Rectf rect( glm::floor( pixel - radius - 1.0F ), glm::ceil( pixel + radius ) );

                paint_circle( app::getElapsedSeconds( ), rect, radius, folder->get_tag( ) );
            }
        }
    }

    // 古いデータは切り捨てます。
    int i = 0;
    for ( ; i < _past_paint_datas.size( ); ++i )
    {
        if ( _past_paint_datas[i].time > app::getElapsedSeconds( ) - 0.5F )
        {
            break;
        }
    }
    _past_paint_datas.erase( _past_paint_datas.begin( ), _past_paint_datas.begin( ) + i );
}
std::vector<std::vector<unsigned char>>& ground_color_manager::get_ground_color_id( )
{
    return _ground_color_id;
}
void ground_color_manager::clear( int const & user_id )
{
    for ( int y = 0; y < _ground_color_id.size( ); ++y )
    {
        for ( int x = 0; x < _ground_color_id[y].size( ); ++x )
        {
            auto& pixel = _ground_color_id[x][y];
            if ( pixel == user_id )
            {
                pixel = 0;
            }
        }
    }
}
void ground_color_manager::insert( float time, cinder::vec2 position, float radius, int user_id )
{
    _is_inserted = true;
    int i = std::max( 0, (int)_past_paint_datas.size( ) - 1 );
    for ( ; i >= 0; --i )
    {
        if ( _past_paint_datas[i].time < time ) break;
    }
    _min_insert_iterator = i;
    _past_paint_datas.insert( _past_paint_datas.begin( ) + i, paint_data( { time, position, radius, user_id } ) );
}
void ground_color_manager::paint_circle( float time, cinder::Rectf rect, float radius, int user_id )
{
    _past_paint_datas.push_back( { time, rect.getCenter( ), radius, user_id } );

    auto ground_size = user_default::get_instans( )->get_root( )["ground_size"].asInt( );
    auto ground_scale = user_default::get_instans( )->get_root( )["ground_scale"].asInt( );

    for ( int y = rect.y1; y <= rect.y2; ++y )
    {
        for ( int x = rect.x1; x <= rect.x2; ++x )
        {
            if ( radius < glm::length( cinder::vec2( x, y ) - rect.getCenter( ) ) ) continue;
            if ( x < 0 || y < 0 || x >= ground_size || y >= ground_size ) continue;
            auto pos = cinder::ivec2( x, y );
            _ground_color_id[pos.x][pos.y] = user_id;
        }
    }
}
}
