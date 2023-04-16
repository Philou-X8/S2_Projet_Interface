/********
* File: main.cpp
* Team: P-6
* Creation Date: April 4th, 2023
* Description: main file of S2_Projet_Interface
* 
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/

#include <QApplication>
#include "window_main.h"

int main( int argc, char ** argv )
{
	QApplication app(argc, argv);
	window_main mainWindow;
	mainWindow.show();
	return app.exec();
}
