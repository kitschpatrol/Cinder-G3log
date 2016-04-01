#include "cinder/System.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "CinderG3log.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class G3logBasicApp : public App {
public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void update() override;
	void draw() override;

private:
	G3logRef log;
	ci::params::InterfaceGlRef mParams;
};

void G3logBasicApp::setup() {
	log = G3log::create("G3logBasic", getAssetPath("logs"), true);

	G3_LOG_V(" OS Version " << System::getOsMajorVersion() << "." << System::getOsMinorVersion() << "." << System::getOsBugFixVersion());

	mParams = params::InterfaceGl::create("Params", ivec2(170, 300));
	mParams->addButton("Verbose", [&]() { G3_LOG_V("Verbose"); }, "key=v");
	mParams->addButton("Debug", [&]() { G3_LOG_D("Debug"); }, "key=d");
	mParams->addButton("Info", [&]() { G3_LOG_I("Info"); }, "key=i");
	mParams->addButton("Warning", [&]() { G3_LOG_W("Warning"); }, "key=w");
	mParams->addButton("Error", [&]() { G3_LOG_E("Error"); }, "key=e");
	mParams->addButton("Fatal", [&]() { G3_LOG_F("Fatal"); }, "key=f");
	mParams->addButton("Force Crash", [&]() { raise(SIGTERM); }, "key=c");
}

void G3logBasicApp::mouseDown(MouseEvent event) {

	LOG(ERROR) << "Event! " << event.getPos();
}

void G3logBasicApp::update() {
}

void G3logBasicApp::draw() {
	gl::clear(Color(0, 0, 0));
	mParams->draw();
}

void G3logBasicApp::keyDown(KeyEvent event) {
	LOG(DBUG) << __FUNCTION__;

	LOG_IF(INFO, event.isShiftDown()) << "Shift key is pressed";
	LOG_IF(INFO, event.isAltDown()) << "Alt key is pressed";
	LOG_IF(INFO, event.isControlDown()) << "Control key is pressed";
}

CINDER_APP(G3logBasicApp, RendererGl)
