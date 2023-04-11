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
	levelCount = 10; // max number of level

	lvlSelection = profile->getUnlocked();
	if (lvlSelection <= levelCount) {
		levelCount = lvlSelection;
	}

	levelsBgTex = new QLabel(this);
	levelsBgTex->setAlignment(Qt::AlignCenter);
	levelsBgTex->setPixmap(profile->getTex("background"));
	levelsBgTex->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	levelsTitle = new QLabel(this);
	levelsTitle->setAlignment(Qt::AlignCenter);
	levelsTitle->setFont(QFont("Impact", 36));
	levelsTitle->setText("LEVEL SELECTION");

	levelsSelectionTexture = new QLabel(this);
	levelsSelectionTexture->setAlignment(Qt::AlignCenter);
	levelsSelectionTexture->setPixmap(profile->getTex("button_base"));

	levelsSelectionText = new QLabel(this);
	levelsSelectionText->setAlignment(Qt::AlignCenter);
	levelsSelectionText->setFont(QFont("Impact", 20));
	levelsSelectionText->setText("LEVEL: " + QString::number(lvlSelection));

	levelsButtonList = new CustomMenu(profile, this);
	QObject::connect(levelsButtonList, SIGNAL(clickedButton(int)), this, SLOT(menuClicked(int)));
	levelsButtonList->addButton("SELECT LEVEL", true);
	levelsButtonList->addButton("CANCEL", false);

	levelsLayout = new QGridLayout(this);
	levelsLayout->setContentsMargins(0, 0, 0, 0);
	// fill layout
	levelsLayout->addWidget(levelsBgTex, 0, 0, 3, 3);
	levelsLayout->addWidget(levelsTitle, 0, 0, 1, 3);
	levelsLayout->addWidget(levelsSelectionTexture, 1, 1);
	levelsLayout->addWidget(levelsSelectionText, 1, 1);
	levelsLayout->addWidget(levelsButtonList, 2, 1);
	//homeLayout->setAlignment(Qt::AlignCenter);

	setLayout(levelsLayout);
}

screen_select_level::~screen_select_level() {
	delete levelsButtonList;
}

void screen_select_level::onKeyEvent(char key) {
	switch (key) {
	case 'a':
	case 'j':
		lvlSelection--;
		if (lvlSelection > levelCount) lvlSelection = 1;
		if (lvlSelection < 1) lvlSelection = levelCount;

		break;
	case 'd':
	case 'l':
		lvlSelection++;
		if (lvlSelection > levelCount) lvlSelection = 1;
		if (lvlSelection < 1) lvlSelection = levelCount;

		break;
	default:
		levelsButtonList->onKeyEvent(key);
		return; // return
	}
	//QString levelText("bruh Level: " + QString::number(lvlSelection));
	levelsSelectionText->setText("LEVEL: " + QString::number(lvlSelection));

}

void screen_select_level::menuClicked(int index) {
	switch (index) {
	case 0:
		profile->setStart(lvlSelection);
		emit SelectScreenSignal(ID_GAME);
		break;
	case 1:
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