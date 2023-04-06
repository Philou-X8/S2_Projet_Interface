#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "userProfile.h"

class screen_select_level : public QWidget
{
	Q_OBJECT
public:
	screen_select_level();
	screen_select_level(UserProfile* p);
	~screen_select_level();

private:
	const int levelCount = 12; // number of existing levels
	UserProfile* profile;
};
