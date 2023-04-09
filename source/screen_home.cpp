#include "screen_home.h"


//-------------------------------------------------------
//	home screen
//-------------------------------------------------------
screen_home::screen_home(UserProfile* p) : QWidget(),
	profile(p),
	homeLayout(nullptr),
	//homeTestText(nullptr),
	levelSelect(nullptr),
	continueGame(nullptr),
	settings(nullptr),
	quit(nullptr),
	buttonList(nullptr)
{
	//profile = p;
	
	homeTitle = new QLabel(this);
	homeTitle->setPixmap(profile->getTex("home_title"));
	homeTitle->setAlignment(Qt::AlignCenter);

	continueGame = new CustomButton(profile->getTex("home_button_continue"), profile->getTex("home_button_hi"));
	levelSelect = new CustomButton(profile->getTex("home_button_level"), profile->getTex("home_button_hi"));
	settings = new CustomButton(profile->getTex("home_button_settings"), profile->getTex("home_button_hi"));
	quit = new CustomButton(profile->getTex("home_button_quit"), profile->getTex("home_button_hi"));

	activeButton = 0;
	buttonList = new QList<CustomButton*>();
	buttonList->append(continueGame);
	buttonList->append(levelSelect);
	buttonList->append(settings);
	buttonList->append(quit);
	buttonList->at(activeButton)->onSelect();

	// create layout
	homeLayout = new QGridLayout(this);
	// fill layout
	homeLayout->addWidget(homeTitle, 0, 0, 1, 1);
	homeLayout->addLayout(continueGame, 1, 0);
	homeLayout->addLayout(levelSelect, 2, 0);
	homeLayout->addLayout(settings, 3, 0);
	homeLayout->addLayout(quit, 4, 0);


	//homeLayout->setAlignment(Qt::AlignCenter);

	setLayout(homeLayout);
	setWindowTitle("test title");
}

screen_home::~screen_home() {

}

void screen_home::onKeyEvent(char key) {
	switch (key)
	{
	case 'w':
	case 'i':
		if (activeButton > 0) {
			buttonList->at(activeButton)->onRelease();
			activeButton--;
			buttonList->at(activeButton)->onSelect();
		}
		break;
	case 's':
	case 'k':
		if (activeButton < 3) {
			buttonList->at(activeButton)->onRelease();
			activeButton++;
			buttonList->at(activeButton)->onSelect();
		}
		break;
	case ' ':
		buttonSelect(activeButton);
		break;
	default:
		break;
	}
}
void screen_home::buttonSelect(int selection) {
	switch (selection)
	{
	case 0:
		emit SelectContinueSignal();
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
}

