/********
* File: window_main.cpp
* Team: P-6
* Creation Date: April 4th, 2023
* Description: Main class of the application
*			   Responsible for the interaction between windows
*			   Responsible for the game's clock
*			   Responsible for the serial communication's clock
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#include "window_main.h"
#include <QApplication>

window_main::window_main(QWidget* parent) : QMainWindow(parent),
	profile(nullptr),
	screenHome(nullptr),
	screenLevels(nullptr),
	screenGame(nullptr),
	screenSettings(nullptr)
{
	profile = new UserProfile;
	inputManager = new InputManager;
	setFocusPolicy(Qt::StrongFocus); // recommended for proper keyboard reading

	screenSettings = new screen_settings(profile, inputManager); 
	QObject::connect(screenSettings, SIGNAL(SelectScreenSignal(int)), this, SLOT(setScreen(int)));

	setScreenHome();

	outputClock = new QTimer;
	QObject::connect(outputClock, SIGNAL(timeout()), this, SLOT(writeOutput()));
	outputClock->start(50);
	inputClock = new QTimer;
	QObject::connect(inputClock, SIGNAL(timeout()), this, SLOT(readInput()));
	inputClock->start(10);

	setMinimumSize(960, 540);
	//setContentsMargins(0, 0, 0, 0);
	//setMaximumSize(1920, 1080);
	//setFixedSize(960, 540);
	//this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//this->adjustSize();
	setFocusPolicy(Qt::StrongFocus);

}
window_main::~window_main() 
{
	inputClock->stop();
	delete inputManager;
}

// (clock function) read input from the queue
void window_main::readInput() {

	char input = inputManager->getInput();
	if (input != 0) { // if the queue is not empty

		if (input == 'p') { // toggle settings visibility
			if (screenSettings->isHidden()) {
				screenSettings->show();
			}
			else {
				screenSettings->hide();
			}
			profile->writeSaveState();
		}

		if (!screenSettings->isHidden()) { // if Settings is shown
			if (input == 'r') { // update sprites
				screenSettings->updateUI();
				if (screenGame != nullptr) screenGame->updateSkin();
				if (screenHome != nullptr) screenHome->updateUI();
				if (screenLevels != nullptr) screenLevels->updateUI();
			}
			screenSettings->onKeyEvent(input); // relay input to the setting window

			return; // return so input doesn't reach other windows
		}

		if (screenHome != nullptr) screenHome->onKeyEvent(input);

		else if (screenLevels != nullptr) screenLevels->onKeyEvent(input);

		else if (screenGame != nullptr) screenGame->onKeyEvent(input);

	}

	// Simulate Muons detection
	int randomNb = QRandomGenerator::global()->bounded( int(6000/30) ); //  6000/ferq (min)
	if (randomNb == 0) {
		inputManager->addKey('m');
	}
}
// (clock function) collect game info and relay it to the input manager
void window_main::writeOutput() {
	int moveCount = 88;
	int ledMode = 2;
	if (screenGame != nullptr) {
		screenGame->getOutputInfo(moveCount, ledMode);
	}
	inputManager->updateOutputInfo(moveCount, ledMode);
}

// called whenever a key is pressed
void window_main::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_M: // discard [m] key (muon)
	case Qt::Key_Shift: // discard [shift] key
		return;
	case Qt::Key_Escape:
	case Qt::Key_Tab:
		inputManager->addKey('p'); // settings window
		return;
	case Qt::Key_Enter:
		inputManager->addKey(' '); // selection key
		return;
	default: // add the input key to the queue
		QChar qchar((char)event->key());
		inputManager->addKey(qchar.toLower().unicode());
		break;
	}
}

// change between screens
void window_main::setScreen(int id) {
	switch (id) {
	case ID_HOME:
		setScreenHome();
		break;
	case ID_GAME:
		setScreenGame();
		break;
	case ID_LEVELS:
		setScreenLevels();
		break;
	case ID_SETTINGS:
		screenSettings->show();
		break;
	case ID_QUIT:
		QApplication::quit();
		break;
	default:
		break;
	}
}

// set central widget to Home
void window_main::setScreenHome() {
	clearCentralWidget();
	if (screenHome == nullptr) {
		screenHome = new screen_home(profile, this);
		QObject::connect(screenHome, SIGNAL(SelectScreenSignal(int)), this, SLOT(setScreen(int)));
	}
	setCentralWidget(screenHome);
	setWindowTitle("Push Pull Escape");
}
// set central widget to Level Selection
void window_main::setScreenLevels() {
	clearCentralWidget();
	if (screenLevels == nullptr) {
		screenLevels = new screen_select_level(profile, this);
		QObject::connect(screenLevels, SIGNAL(SelectScreenSignal(int)), this, SLOT(setScreen(int)));
	}
	setCentralWidget(screenLevels);
	setWindowTitle("Level selection");
}
// set central widget to the game
void window_main::setScreenGame() {
	clearCentralWidget();
	if (screenGame == nullptr) {
		screenGame = new screen_game(profile, this);
	}
	setCentralWidget(screenGame);
	setWindowTitle("Game screen");
}

// remove current central widget
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