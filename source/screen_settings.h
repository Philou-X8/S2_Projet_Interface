/********
* File: screen_settings.h
* Team: P-6
* Creation Date: April 4th, 2023
* Description: UI class used to display the settings page
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QkeyEvent>
#include "custom_menu.h"
#include "inputmanager.h"

class screen_settings : public QWidget
{
	Q_OBJECT
public:
	screen_settings(UserProfile* p, InputManager* inManager);
	~screen_settings();

	void onKeyEvent(char key);
	void updateUI();

signals:
	void SelectScreenSignal(int);

protected:
	// since this window can be on focus instead, the kb listener is needed
	void keyPressEvent(QKeyEvent* event) override;

private:
	
	UserProfile* profile;
	InputManager* inputManager;
	QGridLayout* settingsLayout;
	QLabel* settingsBgTex;
	QLabel* settingsTitle;
	CustomMenu* settingsButtonList;

	void sideToggle(int dir);

};


