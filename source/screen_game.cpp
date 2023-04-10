#include "screen_game.h"

screen_game::screen_game(UserProfile* p) : QWidget(),
	profile(p),
	gameLayout(nullptr),
	p1(nullptr),
	p2(nullptr),
	mapSize(nullptr),
	mapGrid(nullptr),
	mapLoader(nullptr)
{
	// -------------------- Logic elements --------------------

	currentLevel = profile->getStart();
	//currentLevel = 1;
	moveCount = 0;
	activePlayer = 1;

	p1 = new Coords;
	p2 = new Coords;
	mapSize = new Coords(19, 19);
	mapLoader = new MapLoader;


	mapGrid = new subscreen_game_grid(profile, p1, p2);
	loadLevel(currentLevel);

	// -------------------- UI elements --------------------
	QLabel* testLabel = new QLabel(this);
	gameLayout = new QGridLayout(this);
	//gameLayout->setSizeConstraint(QLayout::SetMinimumSize);
	
	gameLayout->addWidget(testLabel, 0, 0, 3, 3);
	gameLayout->addWidget(mapGrid, 1, 1);
	
	setLayout(gameLayout);
}
screen_game::~screen_game() {

}
void screen_game::onKeyEvent(char key) {

	int moveResult = inputPlayerAction(key);
	mapGrid->movePlayers();
	if (moveResult != BLOCKED_MOVE) {

		moveCount++;
	}
	if (mapGrid->mapSolved()) {
		// map solved
		// do some stuff like a pop up of smt
		currentLevel++;
		bool gameOver = !loadLevel(currentLevel);
		if (gameOver) {
			currentLevel = 1;
			// there are no more level
		}
	}
}
bool screen_game::levelState() {
	return false;
}

bool screen_game::loadLevel(int lvl) {
	int lvlToLoad = lvl;
	if (lvlToLoad < 0) lvlToLoad = currentLevel;
	moveCount = 0;
	int map[20][20] = { 0 };
	bool ret = mapLoader->loadMap(&map, p1, p2, mapSize, lvlToLoad);
	mapGrid->newGrid(&map, *mapSize);
	return ret;
}

void screen_game::updateSkin() {
	mapGrid->updateSkin();
}

void screen_game::getOutputInfo(int& count) {
	count = moveCount;
}

int screen_game::inputPlayerAction(char input) {

	switch (input) {
		// ------------------------------- player 1
	case 'w':
		return mapGrid->moveP1(Coords(0, 1));	// up
	case 's':
		return mapGrid->moveP1(Coords(0, -1));	// down
	case 'd':
		return mapGrid->moveP1(Coords(1, 0));	// right
	case 'a':
		return mapGrid->moveP1(Coords(-1, 0));	// left
	case 'f':
		return mapGrid->actionRed();			// action
		// ------------------------------- player 2
	case 'i':
		return mapGrid->moveP2(Coords(0, 1));	// up
	case 'k':
		return mapGrid->moveP2(Coords(0, -1));	// down
	case 'l':
		return mapGrid->moveP2(Coords(1, 0));	// right
	case 'j':
		return mapGrid->moveP2(Coords(-1, 0));	// left
	case 'h':
		return mapGrid->actionBlue();			// action
		// ------------------------------- menus
	case 'r':
		loadLevel(currentLevel);				// restart level
		return BLOCKED_MOVE;
	case 't': 
		activePlayer = 1; // switch to ply 1
		return BLOCKED_MOVE;
	case 'y': 
		activePlayer = 2; // switch to ply 2
		return BLOCKED_MOVE;
	default:
		return BLOCKED_MOVE;
	}
	return BLOCKED_MOVE;
}


