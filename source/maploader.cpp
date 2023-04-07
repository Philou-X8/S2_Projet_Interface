#include "maploader.h"

MapLoader::MapLoader() {
	lvlPathName = "../levels/level";
	//lvlProgress = 0;
	lvlExtension = ".txt";
}
MapLoader::~MapLoader() {

}

bool MapLoader::loadMap(int (*arr)[20][20], Coords* p1, Coords* p2, Coords* mapSize, int lvlNb) {
	//int leftEdge = 19;
	//int rightEdge = 0;
	//int lowEdge = 19;
	//int topEdge = 0;
	// genereate the path to the file that must be loaded
	std::string lvlToLoad = lvlPathName + std::to_string(lvlNb) + lvlExtension;
	int buffer;
	rFile.open(lvlToLoad); // open file
	if (rFile.is_open()) {
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
				/*
				if (buffer != 1) {
					if (x > rightEdge) rightEdge = x;
					if (x < leftEdge) leftEdge = x;
					if (y > topEdge) topEdge = y;
					if (y < lowEdge) lowEdge = y;
				}
				*/
			}
		}
		
		if (!rFile.eof()) { // map size x
			rFile >> buffer;
			mapSize->x = buffer;
		}
		else {
			mapSize->x = 19;
		}
		if (!rFile.eof()) { // map size y
			rFile >> buffer;
			mapSize->y = buffer;
		}
		else {
			mapSize->y = 19;
		}
		
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