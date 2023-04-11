/*
*
*   MAKING A GAME PROTOTYPE FOR SCHOOL
*
*/
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "position.h"


class MapLoader
{
public:
	MapLoader();
	~MapLoader();

	void blankMap(); // create a blank map for manual editing
	
	bool loadMap(
		int(*arr)[20][20], 
		Coords* p1, 
		Coords* p2, 
		int lvlNb
	);
	bool loadMapInfo(
		Coords* mapSize, 
		int& moveCount, 
		int lvlNb
	);

private:

	std::ifstream rFile;
	std::string lvlPathName;
	//int lvlProgress;
	std::string lvlExtension;
};

