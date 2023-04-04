/*
*
*   MAKING A GAME PROTOTYPE FOR SCHOOL
*
*/
#pragma once

#include <iostream>
#include <Windows.h>
#include "position.h"

using namespace std;

class MapGrid
{
public:
	MapGrid();
	MapGrid(Coords* p1pos, Coords* p2pos);
	~MapGrid();
	int& getTile(int x, int y);
	void newGrid(int arr[20][20], Coords newMapSize);
	void placePlayers(Coords* p1pos, Coords* p2pos);
	Coords& editSize();
	int moveP1(Coords dir);
	int moveP2(Coords dir);
	int actionRed();
	int actionBlue();
	bool mapSolved();
	friend ostream& operator <<(ostream& s, MapGrid& grid);

private:
	
	int grid[20][20];
	Coords mapSize;

	Coords* p1;
	Coords* p2;
	Coords p1Dir;
	Coords p2Dir;
};
