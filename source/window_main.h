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
#include "inputmanager.h"

class window_main : public QMainWindow
{
	Q_OBJECT
public:
	window_main();
	~window_main();

signals:

public slots:
	void readInput();

protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
	screen_home* screenHome;
	screen_select_level* screenLevels;
	screen_game* screenGame;

	QTimer* clock;
	InputManager* inputManager;
};

#endif