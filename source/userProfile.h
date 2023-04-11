#pragma once
#include <QWidget>
#include <QList>
#include <QFile>

#define ID_HOME 0
#define ID_GAME 1
#define ID_LEVELS 2
#define ID_SETTINGS 3
#define ID_QUIT 4

class UserProfile
{
public:
	UserProfile();
	~UserProfile();

	void writeSaveState();

	void loadSkinList(QStringList& returnList);

	QPixmap getTex(QString tex);
	int getUnlocked();
	void setUnlocked(int progess);
	int getStart();
	void setStart(int start);
	bool autoPush();
	void setPushMode(bool mode);
	bool autoPull();
	void setPullMode(bool mode);

	QString changeSkin(int dir);
private:
	QString skin;
	int unlockedLvlNb;
	int startingLvl;
	bool pushMode;
	bool pullMode;

	QStringList unlockedSkins;

	void readSaveState();

};

