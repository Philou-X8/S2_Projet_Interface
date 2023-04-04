/********
* Fichier: testGraphicusGUI.cpp
* Auteurs: C.-A. Brunet
* Date: 21 décembre 2021 (création)
* Description: Ce programme teste l'interface usager GraphicusGUI.
*
* Copyright 2022 Département de génie électrique et génie informatique
*                Université de Sherbrooke  
********/

#include <QApplication>

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <mmsystem.h>
#include "maploader.h"
#include "mapgrid.h"
#include "gamemanager.h"

int main( int argc, char ** argv )
{
	InputManager* inputManager = new InputManager();

	QApplication app(argc, argv);
	//MonInterface gui("TestGraphicusGUI 1.0");
	return app.exec();
}
