/********
* File: custom_button.cpp
* Team: P-6
* Creation Date: April 4th, 2023
* Description: UI element used to display a button in CustomMenu
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/

#include "custom_button.h"

CustomButton::CustomButton(UserProfile* p, QString text, bool hasArrow) : QGridLayout(),
	profile(p),
	buttonText(nullptr),
	buttonBase(nullptr),
	buttonHi(nullptr),
	arrowR(nullptr),
	arrowL(nullptr)
{
	buttonText = new QLabel(text);
	buttonText->setAlignment(Qt::AlignCenter);
	buttonText->setFont(QFont("Impact", 16));

	buttonBase = new QLabel;
	buttonBase->setAlignment(Qt::AlignCenter);
	buttonBase->setPixmap(profile->getTex("button_base"));

	buttonHi = new QLabel;
	buttonHi->setAlignment(Qt::AlignCenter);
	buttonHi->setPixmap(profile->getTex("button_hi"));
	buttonHi->hide();

	if (hasArrow) {
		arrowR = new QLabel;
		arrowR->setAlignment(Qt::AlignCenter);
		arrowR->setPixmap(profile->getTex("button_base_arrow_r"));
		arrowL = new QLabel;
		arrowL->setAlignment(Qt::AlignCenter);
		arrowL->setPixmap(profile->getTex("button_base_arrow_l"));

		addWidget(arrowR, 0, 2);
		addWidget(arrowL, 0, 0);
	}

	addWidget(buttonBase, 0, 1);
	addWidget(buttonHi, 0, 1);
	addWidget(buttonText, 0, 1);
}
CustomButton::~CustomButton()
{
	delete buttonBase;
	delete buttonHi;
	if (buttonText != nullptr) delete buttonText;
	if (arrowR != nullptr) delete arrowR;
	if (arrowL != nullptr) delete arrowL;
}
void CustomButton::onSelect() {
	buttonHi->show();
}
void CustomButton::onRelease() {
	buttonHi->hide();
}

void CustomButton::updateText(QString text) {
	if (buttonText != nullptr) {
		buttonText->setText(text);
	}
}
void CustomButton::updateUI() {
	buttonBase->setPixmap(profile->getTex("button_base"));
	buttonHi->setPixmap(profile->getTex("button_hi"));

	if (arrowR != nullptr) arrowR->setPixmap(profile->getTex("button_base_arrow_r"));
	if (arrowL != nullptr) arrowL->setPixmap(profile->getTex("button_base_arrow_l"));
}