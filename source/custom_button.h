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

