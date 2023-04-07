#pragma once
#include <QWidget>
#include <QList>
#include <QFile>
class UserProfile
{
public:
	UserProfile();
	~UserProfile();

	QPixmap getTex(QString tex);
	int getUnlocked();
	void setUnlocked(int progess);
	int getStart();
	void setStart(int start);
	bool autoPush();
	void setPushMode(bool mode);
	bool autoPull();
	void setPullMode(bool mode);
private:
	QString skin;
	int unlockedLvlNb;
	int startingLvl;
	bool pushMode;
	bool pullMode;

	QStringList unlockedSkins;

	void readSaveState();

};

