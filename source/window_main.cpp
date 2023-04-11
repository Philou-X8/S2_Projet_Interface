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
	setFocusPolicy(Qt::StrongFocus); // needed for proper keyboard reading

	screenSettings = new screen_settings(profile, inputManager); 
	QObject::connect(screenSettings, SIGNAL(SelectScreenSignal(int)), this, SLOT(setScreen(int)));

	setScreenHome();

	inputClock = new QTimer;
	QObject::connect(inputClock, SIGNAL(timeout()), this, SLOT(readInput()));
	inputClock->start(10);
	outputClock = new QTimer;
	QObject::connect(inputClock, SIGNAL(timeout()), this, SLOT(writeOutput()));
	outputClock->start(50);

	//setCentralWidget(screenHome);
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
	//inputManager->stopThreads();
	delete inputManager;
}

void window_main::readInput() {
	char input = inputManager->getInput();
	if (input != 0) {
		// do stuff when a key is pressed

		if (input == 'p') { // toggle settings visibility
			if (screenSettings->isHidden()) {
				screenSettings->show();
			}
			else {
				screenSettings->hide();
			}
			profile->writeSaveState();
		}

		if (!screenSettings->isHidden()) { // if setting is shown
			if (input == 'r') {
				screenSettings->updateUI();
				if (screenGame != nullptr) screenGame->updateSkin();
				if (screenHome != nullptr) screenHome->updateUI();
				if (screenLevels != nullptr) screenLevels->updateUI();
			}
			screenSettings->onKeyEvent(input);

			return; // return so input doesn't reach other windows
		}

		if (screenHome != nullptr) screenHome->onKeyEvent(input);

		else if (screenLevels != nullptr) screenLevels->onKeyEvent(input);

		else if (screenGame != nullptr) screenGame->onKeyEvent(input);

	}
}

void window_main::writeOutput() {
	int moveCount = 0;
	int ledMode = 0;
	if (screenGame != nullptr) {
		screenGame->getOutputInfo(moveCount, ledMode);
	}
	inputManager->updateOutputInfo(moveCount, ledMode);
}

void window_main::keyPressEvent(QKeyEvent* event) {

	QChar qchar((char)event->key()); // without casting to char, the program crash
	//if (qchar.unicode() >= 'A' && qchar.unicode() <= 'Z') qchar = qchar.toLower();
	if (event->key() == Qt::Key_Escape) {
		inputManager->addKey('p');
		return;
	}
	inputManager->addKey(qchar.toLower().unicode());

}
void window_main::setScreen(int id) {
	std::cout << "set screen, selection: " << id << std::endl;
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

		break;
	default:
		break;
	}
}

void window_main::setScreenHome() {
	clearCentralWidget();
	if (screenHome == nullptr) {
		screenHome = new screen_home(profile, this);
		// ---------- connect
		QObject::connect(screenHome, SIGNAL(SelectScreenSignal(int)), this, SLOT(setScreen(int)));
		// ----------
	}
	setCentralWidget(screenHome);
	setWindowTitle("Home screen");
}
void window_main::setScreenLevels() {
	clearCentralWidget();
	if (screenLevels == nullptr) {
		screenLevels = new screen_select_level(profile, this);
		// ---------- connect
		QObject::connect(screenLevels, SIGNAL(SelectScreenSignal(int)), this, SLOT(setScreen(int)));
		// ----------
	}
	setCentralWidget(screenLevels);
	setWindowTitle("Level selection");
}

void window_main::setScreenGame() {
	clearCentralWidget();
	if (screenGame == nullptr) {
		screenGame = new screen_game(profile, this);
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