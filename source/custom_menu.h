/********
* File: custom_menu.h
* Team: P-6
* Creation Date: April 4th, 2023
* Description: UI element used to display a list of button
*			   Can be navigated with keys input
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "userProfile.h"
#include "custom_button.h"

class CustomMenu : public QWidget
{
	Q_OBJECT
public:
	CustomMenu(UserProfile* p, QWidget* parent);
	~CustomMenu();

	void onKeyEvent(char key);

	void addButton(QString text, bool hasArrow);
	int getActiveIndex();

	void updateText(int index, QString text);
	void updateUI();

signals:
	void clickedButton(int i);

private:
	UserProfile* profile;
	QGridLayout* menuLayout;
	QList<CustomButton*>* buttonList;
	int activeButton;
	int buttonCount;

};

