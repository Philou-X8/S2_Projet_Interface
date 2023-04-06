#include "screen_game.h"

screen_game::screen_game(UserProfile* p) : QWidget(),
	profile(nullptr),
	gameLayout(nullptr),
	gameTestText(nullptr)
{
	profile = p;

	// create layout
	gameLayout = new QGridLayout(this);

	// create label
	gameTestText = new QLabel(this);
	gameTestText->setText("screen game");

	// fill layout
	gameLayout->addWidget(gameTestText, 0, 0, 1, 1);

	setLayout(gameLayout);
	setWindowTitle("test title");
}
screen_game::screen_game(UserProfile* p, int startPoint) : screen_game(p)
{
	// send startPoint to MapLoader
}
screen_game::~screen_game() {

}