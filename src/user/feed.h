#pragma once
#include "node.h"
namespace user
{
class feed : public node
{
public:
    bool init( cinder::vec2 position, int id );
};
}