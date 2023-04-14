/********
* File: screen_game.cpp
* Team: P-6
* Creation Date: April 4th, 2023
* Description: Manages the interactions between the game and the
*			   rest of the application
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#include "screen_game.h"


// -----------------------------------------------------
// Game Info right side
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
// update text of the message box
void GameInfoRight::updateComment(QString str) {
	passNotif->setText(str);
}
// message whether a new skin has been unlocked
void GameInfoRight::updateSkin(QString str) {
	if (str.size() > 0) {
		skinNotif->setText("NEW SKIN UNLOCKED:\n" + str);
	}
	else {
		skinNotif->setText("\n");
	}
}

// -----------------------------------------------------
// Game Info left side
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
	updateLevel(startLvl); // set text

	moveCounter = new QLabel(this);
	//moveCounter->setText("MOVES LEFT:\n" + QString::number(startMove));
	moveCounter->setAlignment(Qt::AlignCenter);
	moveCounter->setFont(QFont("Impact", 20));
	updateMoves(startMove); // set text

	playerNotif = new QLabel(this);
	playerNotif->setAlignment(Qt::AlignCenter);
	playerNotif->setFont(QFont("Impact", 20));
	playerNotif->setText("Active player:");

	playerIcon = new QLabel(this);
	playerIcon->setAlignment(Qt::AlignCenter);
	updatePlayer(ply); // set text

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
	// -------------------- Background --------------------
	gameBgTex = new QLabel(this);
	gameBgTex->setAlignment(Qt::AlignCenter);
	gameBgTex->setPixmap(profile->getTex("background"));
	gameBgTex->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	// -------------------- Game State --------------------
	currentLevel = profile->getStart();
	activePlayer = 2;
	moveCount = 0;
	ascendingMoves = 0;
	muonCount = 0;
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

}
screen_game::~screen_game() {
	delete gameInfoR;
	delete gameInfoL;
	delete mapGrid;
	delete mapLoader;
	delete mapSize;
	delete p1;
	delete p2;
}
// should be called whenever a key is pressed
void screen_game::onKeyEvent(char key) {
	if (key == 'm') {
		muonCount++;
		return;
	}

	// move players
	int moveResult = inputPlayerAction(key);
	mapGrid->movePlayers();
	if (moveResult != BLOCKED_MOVE) {

		moveCount--;
		ascendingMoves++;
	}

	// check if level is solved
	if (mapGrid->mapSolved()) {
		std::cout << "level " << currentLevel << ": " 
			<< ascendingMoves << " moves, move left: " << moveCount << "\n";
		ascendingMoves = 0;

		currentLevel++;
		gameInfoR->updateComment("Level completed");
		
		// should unlock new skin
		QString newSkin = "";
		if ( (muonCount % 3) == 1) { // 1/3 chance to unlock skin after finishing a level
			
			newSkin = profile->unlockNewSkin(muonCount); // muonCount as seed
			if (newSkin.size() > 0) {
				updateSkin();
			}
		}
		gameInfoR->updateSkin(newSkin);

		// load next level 
		bool gameOver = !loadLevel(currentLevel);
		if (gameOver) {
			// there are no more level
			gameInfoR->updateComment("GAME OVER");
			currentLevel = 1;
			loadLevel(currentLevel); // return to lvl
		}

		// save progress
		if (profile->getUnlocked() < currentLevel) profile->setUnlocked(currentLevel);
	}
	// update info pannels 
	gameInfoL->updateMoves(moveCount);
	gameInfoL->updateLevel(currentLevel);
	gameInfoL->updatePlayer(activePlayer);

	// reset if out of move
	if (moveCount <= 0) { 
		loadLevel(currentLevel);
		gameInfoR->updateComment("Level failed");
	}
}
// load a level (0 to reload current level)
bool screen_game::loadLevel(int lvl) {
	int lvlToLoad = lvl; // level number
	if (lvlToLoad <= 0) lvlToLoad = currentLevel; 
	moveCount = 99; // move left
	ascendingMoves = 0; // used for testing and debugging
	int map[20][20] = { 0 }; // create blank map 
	bool ret = mapLoader->loadMap(&map, p1, p2, lvlToLoad); // fill the map
	mapLoader->loadMapInfo(mapSize, moveCount, lvlToLoad); // load constraints
	mapGrid->newGrid(&map, *mapSize); // send map
	return ret;
}

// update sprites 
void screen_game::updateSkin() {
	gameBgTex->setPixmap(profile->getTex("background"));
	gameInfoL->updatePlayer(activePlayer);
	mapGrid->updateSkin();
}

// collect info to be sent to controller
void screen_game::getOutputInfo(int& count, int& ply) {
	count = moveCount;
	ply = activePlayer;
}

// bind keys to actions
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


