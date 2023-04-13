/********
* File: maploader.cpp
* Team: P-6
* Creation Date: April 4th, 2023
* Description: Read formated level files
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#include "maploader.h"

MapLoader::MapLoader() {
	lvlPathName = "../levels/level";
	//lvlProgress = 0;
	lvlExtension = ".txt";
}
MapLoader::~MapLoader() {

}
bool MapLoader::loadMap(int (*arr)[20][20], Coords* p1, Coords* p2, int lvlNb) {
	
	// genereate the path to the file that must be loaded
	std::string lvlToLoad = lvlPathName + std::to_string(lvlNb) + lvlExtension;
	int buffer;
	rFile.open(lvlToLoad); // open file
	if (rFile.is_open()) {

		rFile >> buffer; // read max move
		rFile >> buffer; // read x size
		rFile >> buffer; // read y size

		for (int y(19); y >= 0; y--) { // read top of grid first
			for (int x(0); x < 20; x++) {

				rFile >> buffer; // read tile from file
				(*arr)[x][y] = buffer; // add tile to map

				// set player to their spawn
				if (buffer == SPAWN1) {
					(*arr)[x][y] = PATH; // replace spawn block by a path block
					*p1 = Coords(x, y); // put ply1 on its spawn
				} 
				if (buffer == SPAWN2) {
					(*arr)[x][y] = PATH; // replace spawn block by a path block
					*p2 = Coords(x, y); // put ply2 on its spawn
				}
			}
		}
		rFile.close();
	}
	else {
		std::cout << "fuck you you cant code (loading level failed)\n";
		return false;
	}
	return true;
	
}
bool MapLoader::loadMapInfo(Coords* mapSize, int& moveCount, int lvlNb) {
	std::string lvlToLoad = lvlPathName + std::to_string(lvlNb) + lvlExtension;
	int buffer;
	rFile.open(lvlToLoad); // open file
	if (rFile.is_open()) {

		rFile >> buffer; // read max move
		moveCount = buffer;
		rFile >> buffer; // read x size
		mapSize->x = buffer;
		rFile >> buffer; // read y size
		mapSize->y = buffer;

		rFile.close();
	}
	else {
		std::cout << "fuck you you cant code (loading level failed)\n";
		return false;
	}
	return true;
}

void MapLoader::blankMap() {
	std::ofstream wFile;
	wFile.open("./blankMap.txt");
	if (wFile.is_open()) {
		for (int i(0); i < 20; i++) {
			for (int j(0); j < 20; j++) {
				wFile << "1 ";
			}
			wFile << std::endl;
		}
		wFile.close();
	}
	else {
		std::cout << "fuck you you cant code\n";
	}
}