#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H


#include <QMainWindow>
#include <QObject>
//#include <QWidget>
//#include <QMenu>
//#include <QAction>
#include "screen_home.h"
#include "screen_select_level.h"
#include "screen_game.h"

class window_main : public QMainWindow
{
	Q_OBJECT
public:
	window_main();
	~window_main();

signals:
	void testSignal();

public slots:
	void testSlot();

private:
	screen_home *screenHome;
};

#endif