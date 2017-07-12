#pragma once
#include <treelike/node.h>
namespace user
{
class bullet : public treelike::node
{
public:
    bool init( int bullet_id, float radius, cinder::vec2 start_position );
    float get_radius( ) const;
private:
    float _radius;
};
}