#include "screen_settings.h"

screen_settings::screen_settings(UserProfile* p, InputManager* inManager) : QWidget(),
	profile(p),
	inputManager(inManager),
	settingsLayout(nullptr),
	settingsTitle(nullptr),
	skinActive(nullptr),
	settingsButtonList(nullptr)
{

	settingsTitle = new QLabel(this);
	settingsTitle->setPixmap(profile->getTex("home_title"));
	settingsTitle->setAlignment(Qt::AlignCenter);

	skinActive = new QLabel(this);
	skinActive->setText(profile->changeSkin(0));
	skinActive->setAlignment(Qt::AlignCenter);


	settingsButtonList = new CustomMenu(profile);
	//QObject::connect(settingsButtonList, SIGNAL(clickedButton(int)), this, SLOT(menuClicked(int)));
	settingsButtonList->addButton("setting_button_resume", "home_button_hi");
	settingsButtonList->addButton("setting_button_skin", "home_button_hi");
	settingsButtonList->addButton("setting_button_volume", "home_button_hi");
	settingsButtonList->addButton("setting_button_reconnect", "home_button_hi");
	settingsButtonList->addButton("setting_button_home", "home_button_hi");
	settingsButtonList->addButton("setting_button_quit", "home_button_hi");


	// create layout
	settingsLayout = new QGridLayout(this);
	// fill layout
	settingsLayout->addWidget(settingsTitle, 0, 0, 1, 3);
	settingsLayout->addWidget(skinActive, 1, 2, 1, 1);
	settingsLayout->addWidget(settingsButtonList, 1, 1, 6, 1);
	//homeLayout->setAlignment(Qt::AlignCenter);

	setLayout(settingsLayout);
	setWindowTitle("settings");
}
screen_settings::~screen_settings() {

}

void screen_settings::onKeyEvent(char key) {
	switch (key) {
	case 'a':
	case 'j':
		sideToggle(-1);
		break;
	case 'd':
	case 'l':
		sideToggle(1);
		break;
	case' ':
		sideToggle(0);
		break;
	default:
		settingsButtonList->onKeyEvent(key);
		break;
	}
}
void screen_settings::sideToggle(int dir) {
	switch (settingsButtonList->getActiveIndex()) {
	case 0: // resume
		if (dir == 0) this->hide();
		break;
	case 1: // skin
		skinChange(dir);
		break;
	case 2: // volume

		break;
	case 3: // connect controller
		inputManager->connectController();
		break;
	case 4: // return home
		emit SelectScreenSignal(ID_HOME);
		this->hide();
		break;
	case 5: // quit
		emit SelectScreenSignal(ID_QUIT);
		break;
	default:
		break;
	}
}

void screen_settings::skinChange(int dir) {
	skinActive->setText(profile->changeSkin(dir));
	inputManager->addKey('r');
}

void screen_settings::keyPressEvent(QKeyEvent* event) {
	QChar qchar((char)event->key()); // without casting to char, the program crash
	if (event->key() == Qt::Key_Escape) {
		inputManager->addKey('p');
		return;
	}
	inputManager->addKey(qchar.toLower().unicode());
}