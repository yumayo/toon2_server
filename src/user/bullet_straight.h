#pragma once
#include "bullet.h"
namespace user
{
class bullet_straight : public bullet
{
public:
    CREATE_H( bullet_straight, int bullet_id, float radius, cinder::vec2 start_position, cinder::vec2 end_position );
    bool init( int bullet_id, float radius, cinder::vec2 start_position, cinder::vec2 end_position );
    void update( float delta );
    float get_time_remaining( ) const;
private:
    float _time_remaining = 0.0F;
};
}