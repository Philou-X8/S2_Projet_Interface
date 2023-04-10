#include "custom_menu.h"


CustomMenu::CustomMenu(UserProfile* p) : QWidget(),
	profile(p),
	menuLayout(nullptr),
	activeButton(0),
	buttonCount(0)
{
	activeButton = 0;
	buttonCount = 0;
	buttonList = new QList<CustomButton*>();
	menuLayout = new QGridLayout(this);

	setLayout(menuLayout);
}
CustomMenu::~CustomMenu() {

}
void CustomMenu::addButton(QString baseTex, QString hiTex) {
	CustomButton* newButton;
	newButton = new CustomButton(profile->getTex("home_button_continue"), profile->getTex("home_button_hi"));
	buttonList->append(newButton);
	menuLayout->addLayout(newButton, buttonCount, 0);
	
	buttonCount++;

	buttonList->at(activeButton)->onSelect(); // show active button
}

void CustomMenu::onKeyEvent(char key) {
	switch (key)
	{
	case 'w':
	case 'i':
		if (activeButton > 0) {
			buttonList->at(activeButton)->onRelease(); // hide last selection
			activeButton--;
			buttonList->at(activeButton)->onSelect(); // show new selection
		}
		break;
	case 's':
	case 'k':
		if (activeButton < buttonCount) {
			buttonList->at(activeButton)->onRelease();
			activeButton++;
			buttonList->at(activeButton)->onSelect();
		}
		break;
	case ' ':
		emit clickedButton(activeButton);
		break;
	default:
		break;
	}
}