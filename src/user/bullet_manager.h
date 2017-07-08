#pragma once
#include <treelike/node.h>
#include "bullet.h"
namespace user
{
class bullet_manager : public treelike::node
{
    int _id = 0;
public:
    CREATE_H( bullet_manager );
    bool init( );
public:
    std::shared_ptr<bullet> add_bullet( cinder::vec2 position, cinder::vec2 direction, int user_id );
    void remove( int bullet_id );
    void clear( int user_id );
};
}