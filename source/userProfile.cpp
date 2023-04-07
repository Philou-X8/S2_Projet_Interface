#include "userProfile.h"

UserProfile::UserProfile() {
	skin = "default";
	startingLvl = 1;

	unlockedLvlNb = 1; // read from file
	actionMode = false;
}

UserProfile::UserProfile(QString set_skin) : UserProfile() {
	skin = set_skin;
	unlockedLvlNb = 1; // read file

	startingLvl = unlockedLvlNb;
	actionMode = false;
}
UserProfile::~UserProfile() {

}

QPixmap UserProfile::getTex(QString tex) {
	QString path = "../texture/" + skin + "/" + tex + ".png";
	return QPixmap(path);
}
int UserProfile::getUnlocked() {
	return unlockedLvlNb;
}
void UserProfile::setUnlocked(int progess) {
	unlockedLvlNb = progess;
}
int UserProfile::getStart() {
	return startingLvl;
}
void UserProfile::setStart(int start) {
	startingLvl = start;
}
bool UserProfile::autoAction() {
	return actionMode;
}
void UserProfile::setActionMode(bool mode) {
	actionMode = mode;
}