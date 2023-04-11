#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H


#include <QMainWindow>
#include <QObject>
//#include <QWidget>
//#include <QMenu>
//#include <QAction>
#include <QkeyEvent>
#include <QTimer>
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
	void readInput();
	void writeOutput();
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
};

#endif