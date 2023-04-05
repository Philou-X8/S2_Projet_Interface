#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QList>

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
	void SelectContinueSignal();

private:
	QGridLayout* homeLayout;
	QLabel* homeTestText;

	QPushButton* levelSelect;
	QPushButton* continueGame;
	QPushButton* settings;
	QPushButton* quit;
	QList<QPushButton*> *buttonList;

	int activeButton;
	void buttonSelect(int selection);

};

class CustomButton : public QLayout
{
	Q_OBJECT
public:
	CustomButton(QPixmap base, QPixmap hi);
	~CustomButton();

	void onSelect();
	void onRelease();
private:
	QLabel* buttonBase;
	QLabel* buttonHi;

};

