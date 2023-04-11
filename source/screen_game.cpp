#include "screen_game.h"


// -----------------------------------------------------
// GameInfoCompletion
// -----------------------------------------------------
GameInfoCompletion::GameInfoCompletion(int ply, QString skin, QWidget* parent) : QWidget(parent),
	infoLayout(nullptr),
	playerNotif(nullptr),
	skinNotif(nullptr)
{
	playerNotif = new QLabel(this);
	playerNotif->setAlignment(Qt::AlignCenter);
	playerNotif->setFont(QFont("Impact", 20));
	this->updatePlayer(ply);

	skinNotif = new QLabel(this); 
	skinNotif->setAlignment(Qt::AlignCenter);
	skinNotif->setFont(QFont("Impact", 20));
	this->updateSkin(skin);

	infoLayout = new QGridLayout(this);
	infoLayout->addWidget(playerNotif, 0, 0);
	infoLayout->addWidget(skinNotif, 1, 0);
}
GameInfoCompletion::~GameInfoCompletion()
{

}

void GameInfoCompletion::updatePlayer(int ply) {
	if (ply == 1) {
		playerNotif->setText("ACTIVE PLAYER:\nRED");
	}
	else {
		playerNotif->setText("ACTIVE PLAYER:\nBLUE");
	}
}
void GameInfoCompletion::updateSkin(QString str) {
	if (str.size() > 0) {
		skinNotif->setText("NEW SKIN UNLOCKED:\n" + str);
	}
	else {
		skinNotif->setText("NO NEW SKIN\n");
	}
}

// -----------------------------------------------------
// gameInfoProgress
// -----------------------------------------------------
GameInfoProgress::GameInfoProgress(int startLvl, int startMove, QWidget* parent) : QWidget(parent),
	infoLayout(nullptr),
	levelCounter(nullptr),
	moveCounter(nullptr)
{
	levelCounter = new QLabel(this);
	levelCounter->setText("LEVEL:\n" + QString::number(startLvl));
	levelCounter->setAlignment(Qt::AlignCenter);
	levelCounter->setFont(QFont("Impact", 20));

	moveCounter = new QLabel(this);
	moveCounter->setText("MOVES LEFT:\n" + QString::number(startMove));
	moveCounter->setAlignment(Qt::AlignCenter);
	moveCounter->setFont(QFont("Impact", 20));

	infoLayout = new QGridLayout(this);
	infoLayout->addWidget(levelCounter, 0, 0);
	infoLayout->addWidget(moveCounter, 1, 0);
}
GameInfoProgress::~GameInfoProgress()
{

}

void GameInfoProgress::updateLevel(int nb) {
	levelCounter->setText("LEVEL:\n" + QString::number(nb));
}
void GameInfoProgress::updateMoves(int nb) {

	moveCounter->setText("MOVES LEFT:\n" + QString::number(nb));
}

// -----------------------------------------------------
// screen_game
// -----------------------------------------------------
screen_game::screen_game(UserProfile* p, QWidget* parent) : QWidget(parent),
	profile(p),
	gameLayout(nullptr),
	infoProgress(nullptr),
	infoCompletion(nullptr),
	p1(nullptr),
	p2(nullptr),
	mapSize(nullptr),
	mapGrid(nullptr),
	mapLoader(nullptr)
{
	// -------------------- Game State --------------------
	currentLevel = profile->getStart();
	moveCount = 0;
	activePlayer = 1;
	// -------------------- Grid Setup --------------------
	p1 = new Coords;
	p2 = new Coords;
	mapSize = new Coords(19, 19);
	mapLoader = new MapLoader;

	mapGrid = new subscreen_game_grid(profile, p1, p2, this);
	loadLevel(currentLevel);
	// -------------------- Info Labels --------------------
	infoProgress = new GameInfoProgress(currentLevel, moveCount, this);
	infoCompletion = new GameInfoCompletion(activePlayer, "", this);
	// -------------------- Layout Filling --------------------
	gameLayout = new QGridLayout(this);
	
	gameLayout->addWidget(mapGrid, 0, 1);
	gameLayout->addWidget(infoProgress, 0, 0);
	gameLayout->addWidget(infoCompletion, 0, 2);
	
	setLayout(gameLayout);
}
screen_game::~screen_game() {
	delete mapGrid;
	delete mapLoader;
	delete mapSize;
	delete p1;
	delete p2;
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

		// save progress
		if (profile->getUnlocked() < currentLevel) profile->setUnlocked(currentLevel);
		
		// should unlock new skin
		QString newSkin = "";
		if ((currentLevel % 3) == 1) { // replace with randomizer
			int seed = 883 * currentLevel; // generate seed
			newSkin = profile->unlockNewSkin(seed); 
		}
		infoCompletion->updateSkin(newSkin);

		bool gameOver = !loadLevel(currentLevel);
		if (gameOver) {
			// there are no more level
			currentLevel = 1;
			loadLevel(currentLevel); // return to lvl
		}
	}
	infoProgress->updateMoves(moveCount);
	infoProgress->updateLevel(currentLevel);
	infoCompletion->updatePlayer(activePlayer);
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

void screen_game::getOutputInfo(int& count, int& ply) {
	count = moveCount;
	ply = activePlayer;
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


