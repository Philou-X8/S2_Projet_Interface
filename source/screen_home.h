#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class screen_home : public QWidget
{
	Q_OBJECT
public:
	screen_home();
	~screen_home();

private:
	QGridLayout* homeLayout;
	QLabel* homeTestText;
};

