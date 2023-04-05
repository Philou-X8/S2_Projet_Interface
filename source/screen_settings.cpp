#include "screen_settings.h"

screen_settings::screen_settings() : QWidget(),
	settingsLayout(nullptr),
	settingsTestText(nullptr)
{
	// create layout
	settingsLayout = new QGridLayout(this);

	// create label
	settingsTestText = new QLabel(this);
	settingsTestText->setText("test text");

	// fill layout
	settingsLayout->addWidget(settingsTestText, 0, 0);

	setLayout(settingsLayout);
	setWindowTitle("test title");
}

screen_settings::~screen_settings() {

}