#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class screen_settings : public QWidget
{
	Q_OBJECT
public:
	screen_settings();
	~screen_settings();

private:
	QGridLayout* settingsLayout;
	QLabel* settingsTestText;
};


