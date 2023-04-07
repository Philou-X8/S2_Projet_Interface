#include "window_main.h"
#include <QApplication>

window_main::window_main(QWidget* parent) : QMainWindow(parent),
	profile(nullptr),
	screenHome(nullptr),
	screenLevels(nullptr),
	screenGame(nullptr)
{
	profile = new UserProfile;
	inputManager = new InputManager;
	setFocusPolicy(Qt::StrongFocus); // needed for proper keyboard reading

	screenHome = new screen_home(profile);
	QObject::connect(screenHome, SIGNAL(SelectLevelSignal()), this, SLOT(setScreenLevels()));
	QObject::connect(screenHome, SIGNAL(SelectContinueSignal()), this, SLOT(setScreenGame()));
	//QObject::connect(screenHome, SIGNAL(SelectLevelSignal()), screenHome, SLOT(testSlot()));
	
	clock = new QTimer;
	QObject::connect(clock, SIGNAL(timeout()), this, SLOT(readInput()));
	clock->start(50);


	setCentralWidget(screenHome);
	setMinimumSize(960, 540);
	//setMaximumSize(1920, 1080);
	//setFixedSize(0, 0);
	//this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//this->adjustSize();
}
window_main::~window_main() 
{
	clock->stop();
	//inputManager->stopThreads();
	delete inputManager;
}

void window_main::readInput() {
	char input = inputManager->getInput();
	if (input != 0) {
		centralWidget()->adjustSize();
		// do stuff when a key is pressed

		if (screenHome != nullptr) screenHome->onKeyEvent(input);

		//if (screenLevels != nullptr) screenLevels->onKeyEvent(input);

		if (screenGame != nullptr) screenGame->onKeyEvent(input);
	}
}

void window_main::keyPressEvent(QKeyEvent* event) {

	QChar qchar((char)event->key()); // without casting to char, the program crash
	//if (qchar.unicode() >= 'A' && qchar.unicode() <= 'Z') qchar = qchar.toLower();
	inputManager->addKey(qchar.toLower().unicode());

}

void window_main::setScreenHome() {
	clearCentralWidget();
	if (screenHome == nullptr) {
		screenHome = new screen_home(profile);
		// ---------- connect
		//QObject::connect(screenHome, SIGNAL(SelectLevelSignal()), this, SLOT(setScreenLevels()));
		//QObject::connect(screenHome, SIGNAL(SelectContinueSignal()), this, SLOT(setScreenGame()));
		// ----------
	}
	setCentralWidget(screenHome);
	setWindowTitle("Home screen");
}
void window_main::setScreenLevels() {
	clearCentralWidget();
	if (screenLevels == nullptr) {
		screenLevels = new screen_select_level(profile);
		// ---------- connect
		
		// ----------
	}
	setCentralWidget(screenLevels);
	setWindowTitle("Level selection");
}

void window_main::setScreenGame() {
	clearCentralWidget();
	if (screenGame == nullptr) {
		screenGame = new screen_game(profile);
		// ---------- connect

		// ----------
	}
	setCentralWidget(screenGame);
	setWindowTitle("Game screen");
}


void window_main::clearCentralWidget() {
	if (screenHome != nullptr) {
		delete screenHome;
		screenHome = nullptr;
	}
	if (screenLevels != nullptr) {
		delete screenLevels;
		screenLevels = nullptr;
	}
	if (screenGame != nullptr) {
		delete screenGame;
		screenGame = nullptr;
	}
}