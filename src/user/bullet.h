#pragma once
#include <treelike/node.h>
namespace user
{
class bullet : public treelike::node
{
public:
    bool init( int bullet_id, float radius, cinder::vec2 start_position );
    float get_radius( ) const;
    cinder::vec2 get_start_position( );
private:
    float _radius;
    cinder::vec2 _start_position;
};
}