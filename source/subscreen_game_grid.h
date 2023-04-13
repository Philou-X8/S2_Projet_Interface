/********
* File: subscreen_game_grid.h
* Team: P-6
* Creation Date: April 4th, 2023
* Description: reponsible for the game's internal logic and its display
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "position.h"
#include "userProfile.h"

class subscreen_game_grid : public QWidget
{
	Q_OBJECT
public:
	subscreen_game_grid(UserProfile* p, Coords* p1pos, Coords* p2pos, QWidget* parent);
	~subscreen_game_grid();

	void newGrid(int(*arr)[20][20], Coords newMapSize);
	void movePlayers();
	bool mapSolved();
	int moveP1(Coords dir);
	int moveP2(Coords dir);
	int actionRed();
	int actionBlue();
	void rotatePlayer(Coords* dir);

	void updateSkin();

	//QGridLayout* playerGrid;
private:
	UserProfile* profile;
	int grid[20][20];
	Coords* p1;
	Coords* p2;
	Coords* p1Dir;
	Coords* p2Dir;
	QLabel* p1Tex;
	QLabel* p2Tex;
	Coords* mapSize;
	QLabel* visualGrid[20][20];
	QGridLayout* gridLayout;
	QPixmap getTileTex(int type);

	//QLabel* spacer;
};

