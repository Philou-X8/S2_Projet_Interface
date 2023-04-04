#include "mapgrid.h"

MapGrid::MapGrid() {
	for (int i(0); i < 20; i++) {
		for (int j(0); j < 20; j++) {
			grid[i][j] = 0;
		}
	}
	mapSize = Coords(19, 19);
	p1 = nullptr;
	p2 = nullptr;

}
MapGrid::MapGrid(Coords* p1pos, Coords* p2pos) {
	for (int i(0); i < 20; i++) {
		for (int j(0); j < 20; j++) {
			grid[i][j] = 0;
		}
	}
	mapSize = Coords(19, 19); // temp
	p1 = p1pos;
	p2 = p2pos;
}
MapGrid::~MapGrid() {
	p1 = nullptr;
	p2 = nullptr;
}


int& MapGrid::getTile(int x, int y) {
	return grid[x][y];
}


void MapGrid::newGrid(int arr[20][20], Coords newMapSize) {
	for (int i(0); i < 20; i++) {
		for (int j(0); j < 20; j++) {
			grid[i][j] = arr[i][j];
		}
	}
	mapSize = newMapSize;
}

void MapGrid::placePlayers(Coords* p1pos, Coords* p2pos) {
	p1 = p1pos;
	p2 = p2pos;
}

Coords& MapGrid::editSize() {
	return mapSize;
}

int MapGrid::moveP1(Coords dir) {
	p1Dir = dir;
	Coords newPos(*p1 + dir);
	switch (grid[newPos.x][newPos.y]) {
	case WALL:
		return 0;
	case SPAWN1:
	case SPAWN2:
	case PATH:
		if (newPos != *p2) *p1 += dir;
		return 1;
	case BOX:
		//return actionRed();
		return 0;
	case GOAL:
		*p1 += dir;
		return 2;
	default:
		break;
	}
	return 0;
}
int MapGrid::moveP2(Coords dir) {
	p2Dir = dir;
	Coords newPos(*p2 + dir);
	switch (grid[newPos.x][newPos.y]) {
	case WALL:
		return 0;
	case SPAWN1:
	case SPAWN2:
	case PATH:
		if (newPos != *p1) *p2 += dir;
		return 1;
	case BOX:
		//return actionBlue();
		return 0;
	case GOAL:
		*p2 += dir;
		return 2;
	default:
		break;
	}
	return 0;
}

int MapGrid::actionRed() {
	
	Coords posBox(*p1 + p1Dir);
	if (grid[posBox.x][posBox.y] != BOX) {
		return 0;
	}
	Coords posBehindBox(posBox + p1Dir);
	if ((grid[posBehindBox.x][posBehindBox.y] == PATH) && (posBehindBox != *p2)) {
		grid[posBehindBox.x][posBehindBox.y] = BOX;
		grid[posBox.x][posBox.y] = PATH;
		*p1 += p1Dir;
		return 1;
	}
	return 0;
}
int MapGrid::actionBlue() {
	Coords posBox(*p2 + p2Dir);
	if (grid[posBox.x][posBox.y] != BOX) {
		return 0;
	}
	Coords posBehindPly(*p2 - p2Dir);
	if ((grid[posBehindPly.x][posBehindPly.y] == PATH) && (posBehindPly != *p1)) {
		grid[p2->x][p2->y] = BOX;
		grid[posBox.x][posBox.y] = PATH;
		*p2 -= p2Dir;
		return 1;
	}
	return 0;
}

bool MapGrid::mapSolved() {
	return (grid[p1->x][p1->y] == GOAL) && (grid[p2->x][p2->y] == GOAL);
}

ostream& operator <<(ostream& s, MapGrid& mapGrid) {
	for (int y(19); y >= 0; y--) { // print top of grid first
		for (int x(0); x <= 19; x++) {
			if (x == mapGrid.p1->x && y == mapGrid.p1->y) {
				s << "(1)";
			}
			else if (x == mapGrid.p2->x && y == mapGrid.p2->y) {
				s << "(2)";
			}
			else {

				switch (mapGrid.getTile(x, y)) {
				case WALL:
					s << char(219) << char(219) << char(219);
					break;
				case SPAWN1:
				case SPAWN2:
				case PATH:
					s << " . ";
					break;
				case BOX:
					s << " " << char(254) << " ";
					break;
				case GOAL:
					s << char(177) << char(177) << char(177);
					break;
				default:
					break;
				}
			}
		}

		s << endl;
	}
	return s;
}
