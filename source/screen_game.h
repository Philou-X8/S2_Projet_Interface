#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "userProfile.h"
#include "maploader.h"
#include "subscreen_game_grid.h"

class screen_game : public QWidget
{
	Q_OBJECT
public:
	screen_game(UserProfile* p, QWidget* parent);
	~screen_game();

	void onKeyEvent(char key);

	bool levelState(); // check if level is finished
	bool loadLevel(int lvl);
	void updateSkin();

	void getOutputInfo(int& count, int& ply);


private:
	UserProfile* profile;
	QGridLayout* gameLayout;

	Coords* p1; // player 1 coords
	Coords* p2; // player 2 coords
	Coords* mapSize;
	subscreen_game_grid* mapGrid;
	MapLoader* mapLoader;
	int currentLevel;
	int moveCount;
	int activePlayer;

	int inputPlayerAction(char input);

};
