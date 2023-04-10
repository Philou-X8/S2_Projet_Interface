#include "screen_home.h"


//-------------------------------------------------------
//	home screen
//-------------------------------------------------------
screen_home::screen_home(UserProfile* p) : QWidget(),
	profile(p),
	homeLayout(nullptr),
	homeButtonList(nullptr)
{
	//profile = p;
	
	homeTitle = new QLabel(this);
	homeTitle->setPixmap(profile->getTex("home_title"));
	homeTitle->setAlignment(Qt::AlignCenter);

	homeButtonList = new CustomMenu(profile);
	QObject::connect(homeButtonList, SIGNAL(clickedButton(int)), this, SLOT(menuClicked(int)));
	homeButtonList->addButton("home_button_continue", "home_button_hi");
	homeButtonList->addButton("home_button_level", "home_button_hi");
	homeButtonList->addButton("home_button_settings", "home_button_hi");
	homeButtonList->addButton("home_button_quit", "home_button_hi");


	// create layout
	homeLayout = new QGridLayout(this);
	// fill layout
	homeLayout->addWidget(homeTitle, 0, 0, 1, 1);
	homeLayout->addWidget(homeButtonList, 1, 0);
	//homeLayout->setAlignment(Qt::AlignCenter);

	setLayout(homeLayout);
	setWindowTitle("test title");
}
screen_home::~screen_home() {

}

void screen_home::onKeyEvent(char key) {
	homeButtonList->onKeyEvent(key);
}
void screen_home::menuClicked(int selection) {
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

