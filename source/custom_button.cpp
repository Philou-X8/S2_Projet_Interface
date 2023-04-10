#include "custom_button.h"

CustomButton::CustomButton(QPixmap base, QPixmap hi) : QGridLayout(),
buttonBase(nullptr),
buttonHi(nullptr),
buttonText(nullptr)
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
	addWidget(buttonText, 0, 0);
}
CustomButton::~CustomButton()
{
	delete buttonBase;
	delete buttonHi;
	if (buttonText != nullptr) delete buttonText;
}
void CustomButton::onSelect() {
	buttonHi->show();
}
void CustomButton::onRelease() {
	buttonHi->hide();
}
