#include "custom_button.h"

CustomButton::CustomButton(QPixmap base, QPixmap hi) : QGridLayout(),
buttonBase(nullptr),
buttonHi(nullptr),
buttonText(nullptr),
arrowR(nullptr),
arrowL(nullptr)
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
	//setAlignment(Qt::AlignCenter);
}
CustomButton::CustomButton(QString text, QPixmap base, QPixmap hi) : CustomButton(base, hi) {
	buttonText = new QLabel(text);
	buttonText->setAlignment(Qt::AlignCenter);
	buttonText->setFont(QFont("Impact", 20));
	addWidget(buttonText, 0, 0);
}
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
	buttonText->setFont(QFont("Impact", 20));

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
