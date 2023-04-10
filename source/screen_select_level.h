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
	screen_select_level(UserProfile* p);
	~screen_select_level();

	void onKeyEvent(char key);

signals:
	void SelectScreenSignal(int);
protected slots:
	void menuClicked(int index);

private:
	const int levelCount = 12; // number of existing levels
	UserProfile* profile;


	QGridLayout* levelsLayout;
	QLabel* levelsTitle;
	QLabel* levelsSelection;
	CustomMenu* levelsButtonList;

	int lvlSelection;
};
