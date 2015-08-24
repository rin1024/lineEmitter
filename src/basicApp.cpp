#include "cinder/app/AppBasic.h"
#include <list>

#include "hrfm.h"
#include "Line.h"

using namespace std;

// We'll create a new Cinder Application by deriving from the AppBasic class
class BasicApp : public hrfm::app::AppBase {
  public:
    void setup();
    void mouseDrag( ci::app::MouseEvent event );
	void keyDown( ci::app::KeyEvent event );
    void update();
    void draw();

	// This will maintain a list of points which we will draw line segments between
	list<Vec2f>		mPoints;
    hrfm::display::DisplayNode _display;
    
protected:
    void onOSC(hrfm::events::OscInputEvent *event) {
        cout << "receive: " << event->message.getAddress() << endl;
    }
};

void BasicApp::setup()
{
    hrfm::app::AppBase::setup();
    hrfm::io::SiOscInput *osc = &hrfm::io::SiOscInput::getInstance();
    osc->addListenPort(2222);
    osc->addEventListener("/hoge", this, &BasicApp::onOSC);
    
    stage.setAutoClear(false);
    stage.addChild(new ::Line());
}

void BasicApp::mouseDrag( ci::app::MouseEvent event )
{
	mPoints.push_back( event.getPos() );
}

void BasicApp::keyDown( ci::app::KeyEvent event )
{
    hrfm::app::AppBase::keyDown(event);
}

void BasicApp::update()
{
    hrfm::app::AppBase::update();
}

void BasicApp::draw()
{
    ci::gl::clear( Color( 0.1f, 0.1f, 0.15f ) );

	ci::gl::color( 1.0f, 0.5f, 0.25f );
	ci::gl::begin( GL_LINE_STRIP );
	for( auto pointIter = mPoints.begin(); pointIter != mPoints.end(); ++pointIter ) {
		ci::gl::vertex( *pointIter );
	}
	ci::gl::end();
    
    hrfm::app::AppBase::draw();
}

// This line tells Cinder to actually create the application
CINDER_APP_BASIC( BasicApp, ci::app::RendererGl )