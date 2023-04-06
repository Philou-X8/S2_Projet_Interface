#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "userProfile.h"

class screen_game : public QWidget
{
	Q_OBJECT
public:
	screen_game(UserProfile* p);
	screen_game(UserProfile* p, int startPoint);
	~screen_game();

private:
	UserProfile* profile;
	QGridLayout* gameLayout;
	QLabel* gameTestText;
};

