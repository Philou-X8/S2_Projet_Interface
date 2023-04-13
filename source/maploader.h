/********
* File: maploader.h
* Team: P-6
* Creation Date: April 4th, 2023
* Description: Read formated level files
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
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

