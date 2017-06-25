#pragma once
#include "node.h"
namespace user
{
class bullet : public node
{
public:
    CREATE_H( bullet, cinder::vec2 position, cinder::vec2 direction, int player_id );
    bool init( cinder::vec2 position, cinder::vec2 direction, int player_id );
    void update( float delta ) override;
    float const& get_radius( ) const;
private:
    cinder::vec2 _direction = cinder::vec2( 0 );
    float _radius = 20.0F;
};
}