/********
* File: custom_menu.cpp
* Team: P-6
* Creation Date: April 4th, 2023
* Description: UI element used to display a list of button
*			   Can be navigated with keys input
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#include "custom_menu.h"


CustomMenu::CustomMenu(UserProfile* p, QWidget* parent) : QWidget(parent),
	profile(p),
	menuLayout(nullptr),
	activeButton(0),
	buttonCount(0)
{
	activeButton = 0;
	buttonCount = 0;
	buttonList = new QList<CustomButton*>(); // list of buttons in the menu
	menuLayout = new QGridLayout(this);

	setLayout(menuLayout);
}
CustomMenu::~CustomMenu() {
	while (!buttonList->isEmpty()) {
		delete buttonList->takeFirst();
	}
	delete buttonList;
}
// add button to the menu
void CustomMenu::addButton(QString text, bool hasArrow) {
	CustomButton* newButton;
	newButton = new CustomButton(profile, text, hasArrow);
	buttonList->append(newButton);
	menuLayout->addLayout(newButton, buttonCount, 0);
	buttonCount++;
	buttonList->at(activeButton)->onSelect(); // show active button
}
// get index of hovered button
int CustomMenu::getActiveIndex() {
	return activeButton;
}
// should be called whenever a key is pressed
void CustomMenu::onKeyEvent(char key) {
	switch (key)
	{
	case 'w': // move up
	case 'i':
		if (activeButton > 0) {
			buttonList->at(activeButton)->onRelease(); // hide last selection
			activeButton--;
			buttonList->at(activeButton)->onSelect(); // show new selection
		}
		break;
	case 's': // move down
	case 'k':
		if (activeButton < (buttonCount - 1)) {
			buttonList->at(activeButton)->onRelease(); // hide last selection
			activeButton++;
			buttonList->at(activeButton)->onSelect(); // show new selection
		}
		break;
	case 'f': // click
	case 'h':
	case ' ':
		emit clickedButton(activeButton);
		break;
	default:
		break;
	}
}
// change text of a given button
void CustomMenu::updateText(int index, QString text) {
	buttonList->at(index)->updateText(text);
}
// update sprites
void CustomMenu::updateUI() {
	for (CustomButton* button : *buttonList) {
		button->updateUI();
	}
}