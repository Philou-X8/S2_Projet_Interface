#include "screen_select_level.h"

screen_select_level::screen_select_level(UserProfile* p) : QWidget(),
	profile(p),
	levelsLayout(nullptr),
	levelsTitle(nullptr),
	levelsButtonList(nullptr)
{
	lvlSelection = profile->getUnlocked();

	levelsTitle = new QLabel(this);
	levelsTitle->setPixmap(profile->getTex("home_title"));
	levelsTitle->setAlignment(Qt::AlignCenter);

	levelsSelection = new QLabel(this);
	QString levelText("bruh Level: " + QString::number(lvlSelection));
	levelsSelection->setText(levelText);

	levelsButtonList = new CustomMenu(profile);
	QObject::connect(levelsButtonList, SIGNAL(clickedButton(int)), this, SLOT(menuClicked(int)));
	levelsButtonList->addButton("setting_button_resume", "home_button_hi");
	levelsButtonList->addButton("setting_button_quit", "home_button_hi");

	levelsLayout = new QGridLayout(this);
	// fill layout
	levelsLayout->addWidget(levelsTitle, 0, 0, 1, 3);
	levelsLayout->addWidget(levelsSelection, 1, 1, 1, 1);
	levelsLayout->addWidget(levelsButtonList, 2, 1, 3, 1);
	//homeLayout->setAlignment(Qt::AlignCenter);

	setLayout(levelsLayout);
}

screen_select_level::~screen_select_level() {

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
	QString levelText("bruh Level: " + QString::number(lvlSelection));
	levelsSelection->setText(levelText);

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