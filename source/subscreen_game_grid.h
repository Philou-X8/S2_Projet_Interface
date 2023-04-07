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
	subscreen_game_grid(UserProfile* p, Coords* p1pos, Coords* p2pos);
	~subscreen_game_grid();

	void newGrid(int(*arr)[20][20], Coords newMapSize);
	bool mapSolved();
	int moveP1(Coords dir);
	int moveP2(Coords dir);
	int actionRed();
	int actionBlue();
	void movePlayers();
	void rotatePlayer(Coords* dir);

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

