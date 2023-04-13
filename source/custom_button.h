/********
* File: custom_button.h
* Team: P-6
* Creation Date: April 4th, 2023
* Description: UI element used to display a button in CustomMenu
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "userProfile.h"

class CustomButton : public QGridLayout
{
	Q_OBJECT
public:
	CustomButton(UserProfile* p, QString text, bool hasArrow);
	~CustomButton();

	void onSelect();
	void onRelease();
	void updateText(QString text);
	void updateUI();
private:
	UserProfile* profile;
	QLabel* buttonText;
	QLabel* buttonBase;
	QLabel* buttonHi;
	QLabel* arrowR;
	QLabel* arrowL;

};

