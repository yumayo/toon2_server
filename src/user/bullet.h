#pragma once
#include "node.h"
namespace user
{
class bullet : public node
{
public:
    bool init( cinder::vec2 position, cinder::vec2 direction, int user_id, int bullet_id );
    void update( float delta ) override;
    float const& get_radius( ) const;
    void set_user_id( int value );
    int const& set_user_id( ) const;
private:
    cinder::vec2 _direction = cinder::vec2( 0 );
    float _radius = 20.0F;
    int user_id = 0;
};
}