/********
* File: screen_home.cpp
* Team: P-6
* Creation Date: April 4th, 2023
* Description: UI class used to display the title screen
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#include "screen_home.h"


//-------------------------------------------------------
//	home screen
//-------------------------------------------------------
screen_home::screen_home(UserProfile* p, QWidget* parent) : QWidget(parent),
	profile(p),
	homeLayout(nullptr),
	homeTitle(nullptr),
	homeBgTex(nullptr),
	homeButtonList(nullptr)
{
	homeBgTex = new QLabel(this);
	homeBgTex->setAlignment(Qt::AlignCenter);
	homeBgTex->setPixmap(profile->getTex("background"));
	homeBgTex->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	homeTitle = new QLabel(this);
	homeTitle->setAlignment(Qt::AlignCenter);
	homeTitle->setFont(QFont("Impact", 64));
	homeTitle->setText("PUSH PULL ESCAPE");

	homeButtonList = new CustomMenu(profile, this);
	QObject::connect(homeButtonList, SIGNAL(clickedButton(int)), this, SLOT(menuClicked(int)));
	homeButtonList->addButton("NEW GAME", false);
	homeButtonList->addButton("SELECT LEVEL", false);
	homeButtonList->addButton("SETTINGS", false);
	homeButtonList->addButton("QUIT", false);


	// create layout
	homeLayout = new QGridLayout(this);
	homeLayout->setContentsMargins(0, 0, 0, 0);

	// fill layout
	homeLayout->addWidget(homeBgTex, 0, 0, 5, 1);
	homeLayout->addWidget(homeTitle, 1, 0);
	homeLayout->addWidget(homeButtonList, 3, 0);
	//homeLayout->setAlignment(Qt::AlignCenter);

	setLayout(homeLayout);
}
screen_home::~screen_home() {
	delete homeButtonList;
}

// should be called whenever a key is pressed
void screen_home::onKeyEvent(char key) {
	homeButtonList->onKeyEvent(key);
}
// pass menu selection to parent 
void screen_home::menuClicked(int selection) {
	if(selection == 0) profile->setStart(1);
	emit SelectScreenSignal(selection+1);
	/*
	switch (selection)
	{
	case 0:
		emit SelectScreenSignal(int(1));
		break;
	case 1:
		emit SelectLevelSignal();
		break;
	case 2:
		emit SelectSettingsSignal();
		break;
	case 3:
		emit SelectQuitSignal();
		break;
	default:
		break;
	}
	*/
}
// update sprites
void screen_home::updateUI() {
	homeBgTex->setPixmap(profile->getTex("background"));
	homeButtonList->updateUI();
}

