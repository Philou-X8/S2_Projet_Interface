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
	int levelCount = 12; // number of existing levels
	UserProfile* profile;

	QGridLayout* levelsLayout;
	QLabel* levelsBgTex;
	QLabel* levelsTitle;
	QLabel* levelsSelectionTexture;
	QLabel* levelsSelectionText;
	CustomMenu* levelsButtonList;

	int lvlSelection;
};
