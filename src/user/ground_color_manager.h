#pragma once
#include <treelike/node.h>
namespace user
{
class ground_color_manager : public treelike::node
{
    softptr<treelike::node> _bullet_manager;
    std::vector<std::vector<unsigned char>> _ground_color_id;
    struct paint_data
    {
        float time;
        cinder::vec2 position;
        float radius;
        int user_id;
    };
    std::vector<paint_data> _past_paint_datas;
    bool _is_inserted = false;
    int _min_insert_iterator = 0;
public:
    CREATE_H( ground_color_manager );
    bool init( );
    void set_bullet_manager( softptr<treelike::node> bullet_manager );
    void update( float delta ) override;
public:
    std::vector<std::vector<unsigned char>>& get_ground_color_id( );
    void clear( int const& user_id );
    void insert( float time, cinder::vec2 position, float radius, int user_id );
    void paint_circle( float time, cinder::Rectf rect, float radius, int id );
};
}