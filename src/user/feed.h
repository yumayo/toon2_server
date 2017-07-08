#pragma once
#include <treelike/node.h>
namespace user
{
class feed : public treelike::node
{
public:
    bool init( cinder::vec2 position, int id );
};
}