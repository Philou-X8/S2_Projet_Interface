/********
* 
* 
* 
********/

#include <QApplication>

//#include <iostream>
//#include <conio.h>
//#include <Windows.h>
//#include <string>
//#include <mmsystem.h>

//#include "maploader.h"
//#include "mapgrid.h"
//#include "gamemanager.h"
#include "window_main.h"

int main( int argc, char ** argv )
{
	QApplication app(argc, argv);
	window_main mainWindow;
	mainWindow.show();
	return app.exec();
}
