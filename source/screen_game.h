#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class screen_game : public QWidget
{
	Q_OBJECT
public:
	screen_game();
	~screen_game();

private:
	QGridLayout* gameLayout;
	QLabel* gameTestText;
};

