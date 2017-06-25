#pragma once
#include "node.h"
namespace user
{
class bullet_manager : public node
{
public:
    CREATE_H( bullet_manager );
    bool init( );
public:
    void clear_bullet_id( int id );
};
}