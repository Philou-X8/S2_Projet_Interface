#include "screen_game.h"

screen_game::screen_game() : QWidget(),
	gameLayout(nullptr),
	gameTestText(nullptr)
{
	// create layout
	gameLayout = new QGridLayout(this);

	// create label
	gameTestText = new QLabel(this);
	gameTestText->setText("test text");

	// fill layout
	gameLayout->addWidget(gameTestText, 0, 0);

	setLayout(gameLayout);
	setWindowTitle("test title");
}

screen_game::~screen_game() {

}