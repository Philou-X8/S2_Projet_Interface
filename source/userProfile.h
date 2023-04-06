#pragma once
#include <QWidget>
class UserProfile
{
public:
	//UserProfile();
	UserProfile(QString set_skin);
	~UserProfile();
	QPixmap getTex(QString tex);
	int getProgress();
private:
	QString skin;
	int unlockedLvlNb;
	int chosenLvl;
};

