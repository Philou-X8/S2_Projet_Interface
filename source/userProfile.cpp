#include "userProfile.h"
/*
UserProfile::UserProfile() {
	skin = "default";
}
*/
UserProfile::UserProfile(QString set_skin) {
	skin = set_skin;
	unlockedLvlNb = 1;

	chosenLvl = unlockedLvlNb;
}
UserProfile::~UserProfile() {

}

QPixmap UserProfile::getTex(QString tex) {
	QString path = "../texture/" + skin + "/" + tex + ".png";
	return QPixmap(path);
}
int UserProfile::getProgress() {
	return unlockedLvlNb;
}