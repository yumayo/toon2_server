#pragma once
#include "scene.h"
#include "receive_data_execute.h"
namespace user
{
class default_scene : public scene
{
    std::unique_ptr<receive_data_execute> _receive_exe;
public:
    CREATE_H( default_scene );
    bool init( );
    receive_data_execute& execute( );
};
}