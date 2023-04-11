#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QkeyEvent>
#include "custom_menu.h"
#include "inputmanager.h"

class screen_settings : public QWidget
{
	Q_OBJECT
public:
	screen_settings(UserProfile* p, InputManager* inManager);
	~screen_settings();

	void onKeyEvent(char key);
	void updateUI();

signals:
	void SelectScreenSignal(int);

protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
	
	UserProfile* profile;
	InputManager* inputManager;
	QGridLayout* settingsLayout;
	QLabel* settingsTitle;
	CustomMenu* settingsButtonList;

	void sideToggle(int dir);

	// skin settings
	//void skinChange(int dir);

};


