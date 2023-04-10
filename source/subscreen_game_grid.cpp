#include "subscreen_game_grid.h"

subscreen_game_grid::subscreen_game_grid(UserProfile* p, Coords* p1pos, Coords* p2pos) : QWidget(),
	profile(p),
	p1(p1pos),
	p2(p2pos),
	p1Dir(nullptr),
	p2Dir(nullptr),
	p1Tex(nullptr),
	p2Tex(nullptr),
	mapSize(nullptr),
	gridLayout(nullptr)
{
	p1Dir = new Coords;
	p2Dir = new Coords;


	mapSize = new Coords(19, 19);

	gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(0);
	//gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
	for (int i(0); i < 20; i++) {
		for (int j(0); j < 20; j++) {
			grid[i][j] = 0;
			visualGrid[i][j] = new QLabel(this);
			visualGrid[i][j]->setPixmap(profile->getTex("board_tile_blank"));
			visualGrid[i][j]->setAlignment(Qt::AlignCenter);
			visualGrid[i][j]->hide();
		}
	}
	setLayout(gridLayout);
	p1Tex = new QLabel(this);
	p1Tex->setPixmap(profile->getTex("player1_d"));
	p1Tex->setAlignment(Qt::AlignCenter);
	p2Tex = new QLabel(this);
	p2Tex->setPixmap(profile->getTex("player2_d"));
	p2Tex->setAlignment(Qt::AlignCenter);

	//this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//adjustSize();
	//playerGrid = new QGridLayout(this);
	//spacer = new QLabel(this);
}
subscreen_game_grid::~subscreen_game_grid() {

}
void subscreen_game_grid::newGrid(int(*arr)[20][20], Coords newMapSize) {
	/*
	if (gridLayout != nullptr) {
		delete gridLayout; // we dont want to delete its content, only the grid
		gridLayout = nullptr;
	} 
	gridLayout = new QGridLayout;
	*/

	*mapSize = newMapSize;
	for (int i = 0; i <20; i++) {
		for (int j = 19; j >= 0; j--) {
			grid[i][j] = (*arr)[i][j];
			visualGrid[i][j]->setPixmap(getTileTex(grid[i][j]));
			if ((i <= mapSize->x) && (j >= 19 - mapSize->y)) {
				visualGrid[i][j]->show();
				gridLayout->addWidget(visualGrid[i][j], 19 - j, i); // check for -1 on Y coords
			}
			else {
				visualGrid[i][j]->hide();
				gridLayout->addWidget(visualGrid[i][j], 0, 0);
			}
			
		}
	}
	*p1Dir = Coords(0, 1);
	*p2Dir = Coords(0, 1);
	movePlayers();
	
	setFixedSize((mapSize->x+1) * 32, (mapSize->y+1) * 32); 
	gridLayout->setContentsMargins(0, 0, 0, 0);
	setContentsMargins(0, 0, 0, 0);
	
	//setFixedSize(0, 0);
	//playerGrid->addWidget(spacer, 0, 0, mapSize->y, mapSize->x);
}
void subscreen_game_grid::movePlayers() {

	rotatePlayer(p1Dir);
	gridLayout->removeWidget(p1Tex);
	gridLayout->addWidget(p1Tex, 19 - p1->y, p1->x);

	rotatePlayer(p2Dir);
	gridLayout->removeWidget(p2Tex);
	gridLayout->addWidget(p2Tex, 19 - p2->y, p2->x);
}

bool subscreen_game_grid::mapSolved() {
	return (grid[p1->x][p1->y] == GOAL) && (grid[p2->x][p2->y] == GOAL);
}

int subscreen_game_grid::moveP1(Coords dir) {
	*p1Dir = dir;
	Coords newPos(*p1 + dir);
	switch (grid[newPos.x][newPos.y]) {
	case WALL:
		return BLOCKED_MOVE;
	case SPAWN1:
	case SPAWN2:
	case PATH:
		if (newPos != *p2) *p1 += dir;
		return VALID_MOVE;
	case BOX:
		if (profile->autoPush()) {
			return actionRed();
		}
		else {
			return BLOCKED_MOVE;
		}
	case GOAL:
		*p1 += dir;
		return VALID_MOVE;
	default:
		return BLOCKED_MOVE;
	}
	return BLOCKED_MOVE;
}
int subscreen_game_grid::moveP2(Coords dir) {
	*p2Dir = dir;
	Coords newPos(*p2 + dir);
	switch (grid[newPos.x][newPos.y]) {
	case WALL:
		return BLOCKED_MOVE;
	case SPAWN1:
	case SPAWN2:
	case PATH:
		if (newPos != *p1) *p2 += dir;
		return VALID_MOVE;
	case BOX:
		if (profile->autoPull()) {
			return actionBlue();
		}
		else {
			return BLOCKED_MOVE;
		}
	case GOAL:
		*p2 += dir;
		return VALID_MOVE;
	default:
		return BLOCKED_MOVE;
	}
	return BLOCKED_MOVE;
}

int subscreen_game_grid::actionRed() {

	Coords posBox(*p1 + *p1Dir);
	if (grid[posBox.x][posBox.y] != BOX) {
		return BLOCKED_MOVE;
	}
	Coords posBehindBox(posBox + *p1Dir);
	if ((grid[posBehindBox.x][posBehindBox.y] == PATH) && (posBehindBox != *p2)) {

		grid[posBehindBox.x][posBehindBox.y] = BOX;
		visualGrid[posBehindBox.x][posBehindBox.y]->setPixmap(getTileTex(BOX));

		grid[posBox.x][posBox.y] = PATH;
		visualGrid[posBox.x][posBox.y]->setPixmap(getTileTex(PATH));

		*p1 += *p1Dir;
		return VALID_MOVE;
	}
	return BLOCKED_MOVE;
}
int subscreen_game_grid::actionBlue() {
	Coords posBox(*p2 + *p2Dir);
	if (grid[posBox.x][posBox.y] != BOX) {
		return BLOCKED_MOVE;
	}
	Coords posBehindPly(*p2 - *p2Dir);
	if ((grid[posBehindPly.x][posBehindPly.y] == PATH) && (posBehindPly != *p1)) {

		grid[p2->x][p2->y] = BOX;
		visualGrid[p2->x][p2->y]->setPixmap(getTileTex(BOX));

		grid[posBox.x][posBox.y] = PATH;
		visualGrid[posBox.x][posBox.y]->setPixmap(getTileTex(PATH));

		*p2 -= *p2Dir;
		return VALID_MOVE;
	}
	return BLOCKED_MOVE;
}

void subscreen_game_grid::rotatePlayer(Coords* dir) {
	if (dir == p1Dir) { // compare pointer, not value
		if (*dir == Coords(1, 0)) {
			p1Tex->setPixmap(profile->getTex("player1_r"));
		}
		else if (*dir == Coords(-1, 0)) {
			p1Tex->setPixmap(profile->getTex("player1_l"));
		}
		else if (*dir == Coords(0, -1)) {
			p1Tex->setPixmap(profile->getTex("player1_d"));
		}
		else { // if (*dir == Coords(0, 1))
			p1Tex->setPixmap(profile->getTex("player1_u"));
		}
	}
	else {
		if (*dir == Coords(1, 0)) {
			p2Tex->setPixmap(profile->getTex("player2_r"));
		}
		else if (*dir == Coords(-1, 0)) {
			p2Tex->setPixmap(profile->getTex("player2_l"));
		}
		else if (*dir == Coords(0, -1)) {
			p2Tex->setPixmap(profile->getTex("player2_d"));
		}
		else { // if (*dir == Coords(0, 1))
			p2Tex->setPixmap(profile->getTex("player2_u"));
		}
	}
}

QPixmap subscreen_game_grid::getTileTex(int type) {
	switch (type) {
	case WALL:
		return profile->getTex("board_tile_wall");
	case PATH:
		return profile->getTex("board_tile_path");		
	case BOX:
		return profile->getTex("board_tile_box");		
	case GOAL:
		return profile->getTex("board_tile_goal");
	case SPAWN1:
		return profile->getTex("board_tile_spawn1");
	case SPAWN2:
		return profile->getTex("board_tile_spawn2");
	default:
		return profile->getTex("board_tile_blank");
	}
}

void subscreen_game_grid::updateSkin() {
	rotatePlayer(p1Dir);
	rotatePlayer(p2Dir);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			visualGrid[i][j]->setPixmap(getTileTex(grid[i][j]));
		}
	}
}
