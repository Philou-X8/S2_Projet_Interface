#include "custom_menu.h"


CustomMenu::CustomMenu(UserProfile* p, QWidget* parent) : QWidget(parent),
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
	while (!buttonList->isEmpty()) {
		delete buttonList->takeFirst();
	}
	delete buttonList;
}
void CustomMenu::addButton(QString text, bool hasArrow) {
	CustomButton* newButton;
	newButton = new CustomButton(profile, text, hasArrow);
	buttonList->append(newButton);
	menuLayout->addLayout(newButton, buttonCount, 0);
	buttonCount++;
	buttonList->at(activeButton)->onSelect(); // show active button
}

int CustomMenu::getActiveIndex() {
	return activeButton;
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
		if (activeButton < (buttonCount - 1)) {
			buttonList->at(activeButton)->onRelease();
			activeButton++;
			buttonList->at(activeButton)->onSelect();
		}
		break;
	case 'f':
	case 'h':
	case ' ':
		emit clickedButton(activeButton);
		break;
	default:
		break;
	}
}

void CustomMenu::updateText(int index, QString text) {
	buttonList->at(index)->updateText(text);
}
void CustomMenu::updateUI() {
	for (CustomButton* button : *buttonList) {
		button->updateUI();
	}
}