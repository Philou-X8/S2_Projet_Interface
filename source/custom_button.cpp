#include "custom_button.h"

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
	//setAlignment(Qt::AlignCenter);
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
