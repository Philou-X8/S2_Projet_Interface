#include "window_main.h"
#include <QApplication>

window_main::window_main() : QMainWindow(),
	screenHome(nullptr) ,
	screenLevels(nullptr) ,
	screenGame(nullptr)
{
	inputManager = new InputManager;
	setFocusPolicy(Qt::StrongFocus);

	QObject::connect(this, SIGNAL(testSignal()), this, SLOT(testSlot()));

	screenHome = new screen_home;
	QObject::connect(screenHome, SIGNAL(SelectLevelSignal()), this, SLOT(testSlot()));
	
	clock = new QTimer;
	QObject::connect(clock, SIGNAL(timeout()), this, SLOT(readInput()));
	clock->start(50);


	setCentralWidget(screenHome);

}

window_main::~window_main() 
{
	inputManager->stopThreads();
	delete inputManager;
}

void window_main::testSlot() {
	screenHome->setNewText("button pressed");
}
void window_main::readInput() {
	char input = inputManager->getInput();
	if (input != 0) {

		// do stuff when a key is pressed

		if (screenHome != nullptr) screenHome->onKeyEvent(input);
	}
}

void window_main::keyPressEvent(QKeyEvent* event) {

	QChar qchar(event->key());
	//qchar = char(event->key());
	//qchar = qchar.toLower();
	inputManager->addKey(qchar.toLower().unicode());

	/*
	QString str;
	//str.append('c');
	str.append((char)event->key());
	str.toLower();
	inputManager->addKey(str.at(0).toLower().unicode());
	screenHome->setNewText(QString(inputManager->getInput()));
	//if (event->key() == Qt::Key_F) 
	*/
}