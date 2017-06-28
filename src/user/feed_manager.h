#pragma once
#include "node.h"
#include "cinder/Rand.h"
#include "feed.h"
namespace user
{
class feed_manager : public node
{
    std::shared_ptr<cinder::Rand> _random_handle;
    int _id = 0;
public:
    CREATE_H( feed_manager );
    bool init( );
    std::shared_ptr<feed> add_feed( );
    void remove( int id );
};
}