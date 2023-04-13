/********
* File: screen_settings.cpp
* Team: P-6
* Creation Date: April 4th, 2023
* Description: UI class used to display the settings page
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#include "screen_settings.h"

screen_settings::screen_settings(UserProfile* p, InputManager* inManager) : QWidget(),
	profile(p),
	inputManager(inManager),
	settingsLayout(nullptr),
	settingsBgTex(nullptr),
	settingsTitle(nullptr),
	settingsButtonList(nullptr)
{

	settingsBgTex = new QLabel(this);
	settingsBgTex->setAlignment(Qt::AlignCenter);
	settingsBgTex->setPixmap(profile->getTex("background"));
	settingsBgTex->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	settingsTitle = new QLabel(this);
	settingsTitle->setAlignment(Qt::AlignCenter);
	//settingsTitle->setPixmap(profile->getTex("home_title"));
	settingsTitle->setFont(QFont("Impact", 36));
	settingsTitle->setText("SETTINGS");

	settingsButtonList = new CustomMenu(profile, this);
	
	settingsButtonList->addButton("RESUME", false);
	settingsButtonList->addButton("SKIN: " + profile->changeSkin(0), true);
	settingsButtonList->addButton("AUTO PUSH: " + QString::number(profile->autoPush()), true);
	settingsButtonList->addButton("AUTO PULL: " + QString::number(profile->autoPull()), true);
	settingsButtonList->addButton("VOLUME: ", true);
	settingsButtonList->addButton("RECONNECT CNT", false);
	settingsButtonList->addButton("RETURN TO HOME", false);
	settingsButtonList->addButton("QUIT", false);


	// create layout
	settingsLayout = new QGridLayout(this);
	settingsLayout->setContentsMargins(0, 0, 0, 0);
	// fill layout
	settingsLayout->addWidget(settingsBgTex, 0, 0, 2, 1);
	settingsLayout->addWidget(settingsTitle, 0, 0);
	settingsLayout->addWidget(settingsButtonList, 1, 0);
	//homeLayout->setAlignment(Qt::AlignCenter);

	setLayout(settingsLayout);
	setWindowTitle("settings");
}
screen_settings::~screen_settings() {
	delete settingsButtonList;
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
		settingsButtonList->updateText(1, "SKIN: " + profile->changeSkin(dir));
		inputManager->addKey('r'); // updates de map's UI
		break;
	case 2: // push
		profile->setPushMode(!profile->autoPush());
		settingsButtonList->updateText(2, "AUTO PUSH: " + QString::number(profile->autoPush()));
		break;
	case 3: // pull
		profile->setPullMode(!profile->autoPull());
		settingsButtonList->updateText(3, "AUTO PULL: " + QString::number(profile->autoPull()));
		break;
	case 4: // volume

		break;
	case 5: // connect controller
		if (dir == 0) inputManager->connectController();
		break;
	case 6: // return home
		if (dir == 0) {
			emit SelectScreenSignal(ID_HOME);
			this->hide();
		}
		break;
	case 7: // quit
		if (dir == 0) emit SelectScreenSignal(ID_QUIT);
		break;
	default:
		break;
	}
}
/*
void screen_settings::skinChange(int dir) {
	//skinActive->setText(profile->changeSkin(dir));
	inputManager->addKey('r');
}
*/

void screen_settings::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_M: // discard [m] key (muon)
	case Qt::Key_Shift:
		return;
	case Qt::Key_Escape:
	case Qt::Key_Tab:
		inputManager->addKey('p');
		return;
	case Qt::Key_Enter:
		inputManager->addKey(' ');
		return;
	default:
		QChar qchar((char)event->key());
		inputManager->addKey(qchar.toLower().unicode());
		break;
	}
}

void screen_settings::updateUI() {
	settingsBgTex->setPixmap(profile->getTex("background"));
	settingsButtonList->updateUI();
}