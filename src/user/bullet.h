#pragma once
#include "node.h"
namespace user
{
class bullet : public node
{
public:
    bool init( cinder::vec2 position, cinder::vec2 direction, int bullet_id );
    void update( float delta ) override;
    float const& get_radius( ) const;
    cinder::vec2 const& get_direction( ) const;
    float const& get_time_remaining( ) const;
private:
    cinder::vec2 _direction = cinder::vec2( 0 );
    float _radius = 20.0F;
    float _time_remaining = 0.0F;
};
}