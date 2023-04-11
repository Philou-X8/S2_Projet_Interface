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
	//CustomButton();
	CustomButton(QPixmap base, QPixmap hi);
	CustomButton(QString text, QPixmap base, QPixmap hi);
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

