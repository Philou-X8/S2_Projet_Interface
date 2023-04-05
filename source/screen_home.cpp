#include "screen_home.h"

screen_home::screen_home() : QWidget(),
	homeLayout(nullptr),
	homeTestText(nullptr)
{
	// create layout
	homeLayout = new QGridLayout(this);

	// create label
	homeTestText = new QLabel(this);
	homeTestText->setText("test text");

	// fill layout
	homeLayout->addWidget(homeTestText, 0, 0);

	setLayout(homeLayout);
	setWindowTitle("test title");
}

screen_home::~screen_home() {

}