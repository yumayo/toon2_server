#pragma once
#include "user/default_scene.h"
#include "scene_manager.h"
inline void entry_point( )
{
    scene_manager::get_instans( )->push( user::default_scene::create( ) );
}