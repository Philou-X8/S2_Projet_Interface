#pragma once

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>


class CustomButton : public QGridLayout
{
	Q_OBJECT
public:
	//CustomButton();
	CustomButton(QPixmap base, QPixmap hi);
	CustomButton(QString text, QPixmap base, QPixmap hi);
	~CustomButton();

	void onSelect();
	void onRelease();
private:
	QLabel* buttonBase;
	QLabel* buttonHi;
	QLabel* buttonText;

};

