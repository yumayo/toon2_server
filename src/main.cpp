#include <treelike/app_delegate.h>
#include "user/default_scene.h"
namespace treelike
{
void setting( cinder::app::App::Settings *settings )
{
    settings->setTitle( u8"toon2_server" );
    settings->setConsoleWindowEnabled( );
}
hardptr<scene> main( )
{
    return user::default_scene::create( );
}
}