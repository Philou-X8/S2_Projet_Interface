#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include "userProfile.h"
#include "custom_button.h"
#include "custom_menu.h"


class screen_home : public QWidget
{
	Q_OBJECT
public:
	screen_home(UserProfile* p, QWidget* parent);
	~screen_home();

	void onKeyEvent(char key);
	void updateUI();

signals:
	void SelectScreenSignal(int);
	//void SelectContinueSignal();
	//void SelectLevelSignal();
	//void SelectSettingsSignal();
	//void SelectQuitSignal();

protected slots:
	void menuClicked(int selection);

private:
	UserProfile* profile;

	QGridLayout* homeLayout;
	QLabel* homeTitle;
	QLabel* homeBgTex;
	CustomMenu* homeButtonList;


};
