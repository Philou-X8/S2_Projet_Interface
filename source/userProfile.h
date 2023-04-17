/********
* File: userProfile.h
* Team: P-6
* Creation Date: April 4th, 2023
* Description: Manage the loading and saving of in-game settings
*			   Manage the loading of sprites
* 
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
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
	void readSaveStateNew();

	void loadSkinList(QStringList& returnList);
	QString unlockNewSkin(int seed);

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

