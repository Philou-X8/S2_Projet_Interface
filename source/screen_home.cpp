#include "screen_home.h"


//-------------------------------------------------------
//	home screen
//-------------------------------------------------------
screen_home::screen_home(UserProfile* p, QWidget* parent) : QWidget(parent),
	profile(p),
	homeLayout(nullptr),
	homeTitle(nullptr),
	homeButtonList(nullptr)
{
	//profile = p;
	
	homeTitle = new QLabel(this);
	homeTitle->setAlignment(Qt::AlignCenter);
	//homeTitle->setPixmap(profile->getTex("home_title"));
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
	// fill layout
	homeLayout->addWidget(homeTitle, 0, 0, 1, 1);
	homeLayout->addWidget(homeButtonList, 1, 0);
	//homeLayout->setAlignment(Qt::AlignCenter);

	setLayout(homeLayout);
	setWindowTitle("test title");
}
screen_home::~screen_home() {
	delete homeButtonList;
}

void screen_home::onKeyEvent(char key) {
	homeButtonList->onKeyEvent(key);
}
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

void screen_home::updateUI() {
	homeButtonList->updateUI();
}

