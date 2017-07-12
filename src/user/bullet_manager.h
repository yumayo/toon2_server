#pragma once
#include <treelike/node.h>
#include "bullet_straight.h"
namespace user
{
class bullet_manager : public treelike::node
{
    int _id = 0;
public:
    CREATE_H( bullet_manager );
    bool init( );
public:
    std::shared_ptr<bullet_straight> add_bullet( int user_id, float radius, cinder::vec2 start_position, cinder::vec2 end_position );
    void remove( int bullet_id );
    void clear( int user_id );
};
}