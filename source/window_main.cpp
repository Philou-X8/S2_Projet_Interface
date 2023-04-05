#include "window_main.h"
#include <QApplication>

window_main::window_main() : QMainWindow(),
	screenHome(nullptr) 
{

	QObject::connect(this, SIGNAL(testSignal()), this, SLOT(testSlot()));

	screenHome = new screen_home;
	setCentralWidget(screenHome);

}

window_main::~window_main() 
{

}

void window_main::testSlot() {

}