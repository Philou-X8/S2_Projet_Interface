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

	void addButton(QString baseTex, QString hiTex);
	void addButton(QString text, QString baseTex, QString hiTex);
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

