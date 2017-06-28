#pragma once
#include "node.h"
namespace user
{
class ground_color_manager : public node
{
    std::weak_ptr<node> _bullet_manager;
    std::vector<std::vector<unsigned char>> _ground_color_id;
public:
    CREATE_H( ground_color_manager );
    bool init( );
    void set_bullet_manager( std::weak_ptr<node> bullet_manager );
    void update( float delta ) override;
public:
    std::vector<std::vector<unsigned char>>& get_ground_color_id( );
    void clear( int const& user_id );
    void paint_circle( cinder::Rectf rect, float radius, int id );
};
}