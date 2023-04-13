/********
* File: userProfile.h
* Team: P-6
* Creation Date: April 4th, 2023
* Description: Main class of the application
*			   Responsible for the interaction between windows
*			   Responsible for the game's clock
*			   Responsible for the serial communication's clock
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H


#include <QMainWindow>
#include <QObject>
#include <QkeyEvent>
#include <QTimer>
#include <QRandomGenerator>
#include "screen_home.h"
#include "screen_select_level.h"
#include "screen_game.h"
#include "screen_settings.h"
#include "inputmanager.h"

class window_main : public QMainWindow
{
	Q_OBJECT
public:
	window_main(QWidget* parent = nullptr);
	~window_main();

signals:

public slots:
	void readInput(); // clock function
	void writeOutput(); // clock function
	void setScreen(int);
	void setScreenHome();
	void setScreenLevels();
	void setScreenGame();

protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
	UserProfile* profile;
	screen_home* screenHome;
	screen_select_level* screenLevels;
	screen_game* screenGame;
	screen_settings* screenSettings;

	QTimer* inputClock;
	QTimer* outputClock;
	InputManager* inputManager;

	void clearCentralWidget();

	int temp;
};

#endif