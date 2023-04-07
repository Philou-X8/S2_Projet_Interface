#pragma once
#include <QWidget>
class UserProfile
{
public:
	UserProfile();
	UserProfile(QString set_skin);
	~UserProfile();

	QPixmap getTex(QString tex);
	int getUnlocked();
	void setUnlocked(int progess);
	int getStart();
	void setStart(int start);
	bool autoAction();
	void setActionMode(bool mode);
private:
	QString skin;
	int unlockedLvlNb;
	int startingLvl;
	bool actionMode; // push/pull box when running into them
};

