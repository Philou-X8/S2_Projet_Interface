#include "screen_home.h"

//-------------------------------------------------------
//	custom button
//-------------------------------------------------------
CustomButton::CustomButton(QPixmap base, QPixmap hi) : QGridLayout(),
	buttonBase(nullptr),
	buttonHi(nullptr)
{
	buttonBase = new QLabel;
	buttonBase->setAlignment(Qt::AlignCenter);
	buttonBase->setPixmap(base);

	buttonHi = new QLabel;
	buttonHi->setAlignment(Qt::AlignCenter);
	buttonHi->setPixmap(hi);
	buttonHi->hide();

	addWidget(buttonHi, 0, 0);
	addWidget(buttonBase, 0, 0);
	setAlignment(Qt::AlignCenter);
}
CustomButton::~CustomButton()
{
	delete buttonBase;
	delete buttonHi;
}
void CustomButton::onSelect() {
	buttonHi->show();
}
void CustomButton::onRelease() {
	buttonHi->hide();
}



//-------------------------------------------------------
//	home screen
//-------------------------------------------------------
screen_home::screen_home(UserProfile* p) : QWidget(),
	homeLayout(nullptr),
	//homeTestText(nullptr),
	levelSelect(nullptr),
	continueGame(nullptr),
	settings(nullptr),
	quit(nullptr),
	buttonList(nullptr)
{
	profile = p;
	
	// create label
	//homeTestText = new QLabel(this);
	//homeTestText->setText("test text");

	homeTitle = new QLabel(this);
	homeTitle->setPixmap(profile->getTex("home_title"));

	continueGame = new CustomButton(profile->getTex("home_button_continue"), profile->getTex("home_button_hi"));
	levelSelect = new CustomButton(profile->getTex("home_button_level"), profile->getTex("home_button_hi"));
	settings = new CustomButton(profile->getTex("home_button_settings"), profile->getTex("home_button_hi"));
	quit = new CustomButton(profile->getTex("home_button_quit"), profile->getTex("home_button_hi"));

	// create layout
	homeLayout = new QGridLayout(this);
	// fill layout
	//homeLayout->addWidget(homeTestText, 0, 0, 1, 1);
	homeLayout->addWidget(homeTitle, 0, 0, 1, 1);
	homeLayout->addLayout(continueGame, 1, 0);
	homeLayout->addLayout(levelSelect, 2, 0);
	homeLayout->addLayout(settings, 3, 0);
	homeLayout->addLayout(quit, 4, 0);

	setLayout(homeLayout);
	setWindowTitle("test title");

	buttonList = new QList<CustomButton*>();
	buttonList->append(continueGame);
	buttonList->append(levelSelect);
	buttonList->append(settings);
	buttonList->append(quit);
	activeButton = 0;
	buttonList->at(activeButton)->onSelect();
}

screen_home::~screen_home() {

}

void screen_home::onKeyEvent(char key) {
	//homeTestText->setText(QString(key));

	switch (key)
	{
	case 'w':
	case 'i':
		if (activeButton > 0) {
			buttonList->at(activeButton)->onRelease();
			//buttonList[activeButton]->onRelease();
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
		emit SelectLevelSignal();
		break;
	case 1:
		emit SelectContinueSignal();
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}
void screen_home::setNewText(QString text) {
	//homeTestText->setText(text);
}


