/********
* File: screen_select_level.h
* Team: P-6
* Creation Date: April 4th, 2023
* Description: UI class used to display the selection of a level
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "userProfile.h"
#include "custom_menu.h"

class screen_select_level : public QWidget
{
	Q_OBJECT
public:
	screen_select_level(UserProfile* p, QWidget* parent);
	~screen_select_level();

	void onKeyEvent(char key);
	void updateUI();

signals:
	void SelectScreenSignal(int);
protected slots:
	void menuClicked(int index);

private:
	int levelCount; // number of existing levels
	int lvlSelection; // currently selected level
	UserProfile* profile;

	QGridLayout* levelsLayout;
	QLabel* levelsBgTex;
	QLabel* levelsTitle;
	QLabel* levelsSelectionTexture;
	QLabel* levelsSelectionText;
	CustomMenu* levelsButtonList;

};
