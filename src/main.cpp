#include "app_delegate.h"
#include "cinder/app/RendererGl.h"
CINDER_APP( app_delegate, cinder::app::RendererGl, [ & ] ( cinder::app::App::Settings *settings )
{
    settings->setConsoleWindowEnabled( );
    settings->setWindowSize( 1280, 720 );
    settings->setTitle( u8"toon2_matching_room" );
    settings->setResizable( false );
} )