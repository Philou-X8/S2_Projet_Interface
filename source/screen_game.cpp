#include "screen_game.h"


// -----------------------------------------------------
// GameInfoCompletion
// -----------------------------------------------------
GameInfoRight::GameInfoRight(QString skin, UserProfile* p, QWidget* parent) : QWidget(parent),
	profile(p),
	infoLayout(nullptr),
	passNotif(nullptr),
	skinNotif(nullptr)
{

	passNotif = new QLabel(this);
	passNotif->setAlignment(Qt::AlignCenter);
	passNotif->setFont(QFont("Impact", 20));
	passNotif->setText("Welcome");

	skinNotif = new QLabel(this); 
	skinNotif->setAlignment(Qt::AlignCenter);
	skinNotif->setFont(QFont("Impact", 20));
	this->updateSkin(skin);

	infoLayout = new QGridLayout(this);
	infoLayout->addWidget(passNotif, 0, 0);
	infoLayout->addWidget(skinNotif, 1, 0);
	setLayout(infoLayout);
}
GameInfoRight::~GameInfoRight()
{

}

void GameInfoRight::updateComment(QString str) {
	passNotif->setText(str);
}
void GameInfoRight::updateSkin(QString str) {
	if (str.size() > 0) {
		skinNotif->setText("NEW SKIN UNLOCKED:\n" + str);
	}
	else {
		skinNotif->setText("\n");
	}
}

// -----------------------------------------------------
// gameInfoProgress
// -----------------------------------------------------
GameInfoLeft::GameInfoLeft(int startLvl, int startMove, int ply, UserProfile* p, QWidget* parent) : QWidget(parent),
	profile(p),
	infoLayout(nullptr),
	levelCounter(nullptr),
	moveCounter(nullptr),
	playerNotif(nullptr),
	playerIcon(nullptr)
{
	levelCounter = new QLabel(this);
	//levelCounter->setText("LEVEL:\n" + QString::number(startLvl));
	levelCounter->setAlignment(Qt::AlignCenter);
	levelCounter->setFont(QFont("Impact", 20));
	updateLevel(startLvl);

	moveCounter = new QLabel(this);
	//moveCounter->setText("MOVES LEFT:\n" + QString::number(startMove));
	moveCounter->setAlignment(Qt::AlignCenter);
	moveCounter->setFont(QFont("Impact", 20));
	updateMoves(startMove);

	playerNotif = new QLabel(this);
	playerNotif->setAlignment(Qt::AlignCenter);
	playerNotif->setFont(QFont("Impact", 20));
	playerNotif->setText("Active player:");

	playerIcon = new QLabel(this);
	playerIcon->setAlignment(Qt::AlignCenter);
	updatePlayer(ply);

	infoLayout = new QGridLayout(this);
	infoLayout->addWidget(levelCounter, 0, 0);
	infoLayout->addWidget(moveCounter, 1, 0);
	infoLayout->addWidget(playerNotif, 2, 0);
	infoLayout->addWidget(playerIcon, 3, 0);
	setLayout(infoLayout);
}
GameInfoLeft::~GameInfoLeft()
{

}

void GameInfoLeft::updateLevel(int nb) {
	levelCounter->setText("LEVEL:\n" + QString::number(nb));
}
void GameInfoLeft::updateMoves(int nb) {

	moveCounter->setText("MOVES LEFT:\n" + QString::number(nb));
}
void GameInfoLeft::updatePlayer(int ply) {
	if (ply == 1) {
		playerIcon->setPixmap(profile->getTex("player1_u"));
	}
	else {
		playerIcon->setPixmap(profile->getTex("player2_u"));
	}
}

// -----------------------------------------------------
// screen_game
// -----------------------------------------------------
screen_game::screen_game(UserProfile* p, QWidget* parent) : QWidget(parent),
	profile(p),
	gameLayout(nullptr),
	gameInfoL(nullptr),
	gameInfoR(nullptr),
	gameBgTex(nullptr),
	p1(nullptr),
	p2(nullptr),
	mapSize(nullptr),
	mapGrid(nullptr),
	mapLoader(nullptr)
{
	gameBgTex = new QLabel(this);
	gameBgTex->setAlignment(Qt::AlignCenter);
	gameBgTex->setPixmap(profile->getTex("background"));
	gameBgTex->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
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
	gameInfoL = new GameInfoLeft(currentLevel, moveCount, activePlayer, profile, this);
	gameInfoR = new GameInfoRight("", profile, this);

	// -------------------- Layout Filling --------------------
	gameLayout = new QGridLayout(this);
	gameLayout->setContentsMargins(0, 0, 0, 0);
	
	gameLayout->addWidget(gameBgTex, 0, 0, 3, 3);
	gameLayout->addWidget(mapGrid, 1, 1);
	gameLayout->addWidget(gameInfoL, 1, 0);
	gameLayout->addWidget(gameInfoR, 1, 2);
	
	setLayout(gameLayout);

	tempCounter = 0;
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

		moveCount--;
		tempCounter++;
	}
	if (mapGrid->mapSolved()) {
		std::cout << "level " << currentLevel << ", " << tempCounter << " moves\n";
		tempCounter = 0;

		currentLevel++;
		gameInfoR->updateComment("Level completed");
		// save progress
		if (profile->getUnlocked() < currentLevel) profile->setUnlocked(currentLevel);
		
		// should unlock new skin
		QString newSkin = "";
		if ((currentLevel % 3) == 1) { // replace with randomizer
			int seed = 883 * currentLevel; // generate seed
			newSkin = profile->unlockNewSkin(seed); 
		}
		gameInfoR->updateSkin(newSkin);

		bool gameOver = !loadLevel(currentLevel);
		if (gameOver) {
			// there are no more level
			currentLevel = 1;
			loadLevel(currentLevel); // return to lvl
		}
	}
	gameInfoL->updateMoves(moveCount);
	gameInfoL->updateLevel(currentLevel);
	gameInfoL->updatePlayer(activePlayer);
	if (moveCount <= 0) { // reset if out of move
		loadLevel(currentLevel);
		gameInfoR->updateComment("Level failed");
	}
}
bool screen_game::levelState() {
	return false;
}

bool screen_game::loadLevel(int lvl) {
	int lvlToLoad = lvl;
	if (lvlToLoad <= 0) lvlToLoad = currentLevel;
	moveCount = 99;
	int map[20][20] = { 0 };
	bool ret = mapLoader->loadMap(&map, p1, p2, lvlToLoad);
	mapLoader->loadMapInfo(mapSize, moveCount, lvlToLoad);
	mapGrid->newGrid(&map, *mapSize);
	return ret;
}

void screen_game::updateSkin() {
	gameBgTex->setPixmap(profile->getTex("background"));
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
		gameInfoR->updateComment("Reloaded level");
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


