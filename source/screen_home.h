#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class screen_home : public QWidget
{
	Q_OBJECT
public:
	screen_home();
	~screen_home();

	void setNewText(QString text);
	void onKeyEvent(char key);

signals:
	void SelectLevelSignal();

private:
	QGridLayout* homeLayout;
	QLabel* homeTestText;

	QPushButton* levelSelect;
	QPushButton* continueGame;
	QPushButton* settings;
	QPushButton* quit;

	int activeButton;

};

