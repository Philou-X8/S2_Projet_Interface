#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include "userProfile.h"
#include "custom_button.h"




class screen_home : public QWidget
{
	Q_OBJECT
public:
	screen_home(UserProfile* p);
	~screen_home();

	void onKeyEvent(char key);

signals:
	void SelectContinueSignal();
	void SelectLevelSignal();
	void SelectSettingsSignal();
	void SelectQuitSignal();

private:
	UserProfile* profile;

	QGridLayout* homeLayout;
	//QLabel* homeTestText; // temp 
	QLabel* homeTitle;
	CustomButton* levelSelect;
	CustomButton* continueGame;
	CustomButton* settings;
	CustomButton* quit;
	QList<CustomButton*> *buttonList;

	int activeButton;
	void buttonSelect(int selection);

};
