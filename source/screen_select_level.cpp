/********
* File: screen_select_level.cpp
* Team: P-6
* Creation Date: April 4th, 2023
* Description: UI class used to display the selection of a level
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#include "screen_select_level.h"

screen_select_level::screen_select_level(UserProfile* p, QWidget* parent) : QWidget(parent),
	profile(p),
	levelsLayout(nullptr),
	levelsBgTex(nullptr),
	levelsTitle(nullptr),
	levelsSelectionTexture(nullptr),
	levelsSelectionText(nullptr),
	levelsButtonList(nullptr)
{
	levelCount = 17; // max number of level

	// cap the level selection wheel to the number of unlocked level
	lvlSelection = profile->getUnlocked();
	if (lvlSelection <= levelCount) {
		levelCount = lvlSelection;
	}

	levelsBgTex = new QLabel(this); // background
	levelsBgTex->setAlignment(Qt::AlignCenter);
	levelsBgTex->setPixmap(profile->getTex("background"));
	levelsBgTex->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	levelsTitle = new QLabel(this); // title
	levelsTitle->setAlignment(Qt::AlignCenter);
	levelsTitle->setFont(QFont("Impact", 36));
	levelsTitle->setText("LEVEL SELECTION");

	levelsSelectionTexture = new QLabel(this); // pannel of currently selected
	levelsSelectionTexture->setAlignment(Qt::AlignCenter);
	levelsSelectionTexture->setPixmap(profile->getTex("button_base"));

	levelsSelectionText = new QLabel(this); // text display of currently selected
	levelsSelectionText->setAlignment(Qt::AlignCenter);
	levelsSelectionText->setFont(QFont("Impact", 20));
	levelsSelectionText->setText("LEVEL: " + QString::number(lvlSelection));

	levelsButtonList = new CustomMenu(profile, this); 
	QObject::connect(levelsButtonList, SIGNAL(clickedButton(int)), this, SLOT(menuClicked(int)));
	levelsButtonList->addButton("SELECT LEVEL", true);
	levelsButtonList->addButton("CANCEL", false);

	// layout
	levelsLayout = new QGridLayout(this);
	levelsLayout->setContentsMargins(0, 0, 0, 0);

	levelsLayout->addWidget(levelsBgTex, 0, 0, 3, 3);
	levelsLayout->addWidget(levelsTitle, 0, 0, 1, 3);
	levelsLayout->addWidget(levelsSelectionTexture, 1, 1);
	levelsLayout->addWidget(levelsSelectionText, 1, 1);
	levelsLayout->addWidget(levelsButtonList, 2, 1);

	setLayout(levelsLayout);
}

screen_select_level::~screen_select_level() {
	delete levelsButtonList;
}
// should be called whenever a key is pressed
void screen_select_level::onKeyEvent(char key) {
	switch (key) {
	case 'a': // move left
	case 'j':
		lvlSelection--;
		if (lvlSelection > levelCount) lvlSelection = 1;
		if (lvlSelection < 1) lvlSelection = levelCount;
		break;
	case 'd': // move right 
	case 'l':
		lvlSelection++;
		if (lvlSelection > levelCount) lvlSelection = 1;
		if (lvlSelection < 1) lvlSelection = levelCount;
		break;
	default:  // click
		levelsButtonList->onKeyEvent(key);
		return; // must return here because levelsSelectionText gets deleted
	}
	levelsSelectionText->setText("LEVEL: " + QString::number(lvlSelection));

}

void screen_select_level::menuClicked(int index) {
	switch (index) {
	case 0: // start game 
		profile->setStart(lvlSelection);
		emit SelectScreenSignal(ID_GAME);
		break;
	case 1: // return to menu
		emit SelectScreenSignal(ID_HOME);
		break;
	default:
		break;
	}
}

void screen_select_level::updateUI() {
	levelsBgTex->setPixmap(profile->getTex("background"));
	levelsSelectionTexture->setPixmap(profile->getTex("button_base"));
	levelsButtonList->updateUI();
}