#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "userProfile.h"
#include "maploader.h"
#include "subscreen_game_grid.h"

class GameInfoRight : public QWidget
{
	Q_OBJECT
public:
	GameInfoRight(QString skin, UserProfile* p, QWidget* parent);
	~GameInfoRight();

	void updateComment(QString text);
	void updateSkin(QString skin);
private:
	UserProfile* profile;
	QGridLayout* infoLayout;
	QLabel* passNotif;
	QLabel* skinNotif;

};
class GameInfoLeft : public QWidget
{
	Q_OBJECT
public:
	GameInfoLeft(int startLvl, int startMove, int ply, UserProfile* p, QWidget* parent);
	~GameInfoLeft();

	void updateLevel(int nb);
	void updateMoves(int nb);
	void updatePlayer(int ply);

private:
	UserProfile* profile;
	QGridLayout* infoLayout;
	QLabel* levelCounter;
	QLabel* moveCounter;
	QLabel* playerNotif;
	QLabel* playerIcon;

};

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
	GameInfoLeft* gameInfoL;
	GameInfoRight* gameInfoR;

	Coords* p1; // player 1 coords
	Coords* p2; // player 2 coords
	Coords* mapSize;
	subscreen_game_grid* mapGrid;
	MapLoader* mapLoader;
	int currentLevel;
	int moveCount;
	int activePlayer;

	int inputPlayerAction(char input);

	int tempCounter;

};
