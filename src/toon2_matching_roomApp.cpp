#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "connection_server.h"
using namespace cinder;
using namespace cinder::app;
class toon2_matching_roomApp : public App
{
    connection_server _receiver;
    float _prev_elapsed_seconds = 0.0F;
    float _delta_seconds = 0.0F;
    float _gradation_seed = 0.0F;
public:
    void setup( ) override;
    void update( ) override;
    void draw( ) override;
};
void toon2_matching_roomApp::setup( )
{
}
void toon2_matching_roomApp::update( )
{
    _delta_seconds = getElapsedSeconds( ) - _prev_elapsed_seconds;
    _prev_elapsed_seconds = getElapsedSeconds( );
    _gradation_seed += _delta_seconds;
    _receiver.update( );
}
void toon2_matching_roomApp::draw( )
{
    using namespace cinder::gl;
    float red = sin( _gradation_seed ) * 0.5F + 0.5F;
    clear( Color( red, red, red ) );
}
CINDER_APP( toon2_matching_roomApp, RendererGl, [ & ] ( App::Settings *settings )
{
    settings->setConsoleWindowEnabled( );
    settings->setWindowSize( 1280, 720 );
    settings->setTitle( u8"toon2_matching_room" );
    settings->setResizable( false );
} )
