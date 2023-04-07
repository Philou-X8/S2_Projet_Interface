#include "userProfile.h"

UserProfile::UserProfile() :
	skin("default"),
	unlockedLvlNb(1),
	startingLvl(1),
	pushMode(false),
	pullMode(false)
{
	readSaveState();
}
UserProfile::~UserProfile() {

}

void UserProfile::readSaveState() {
	QFile file("../configs/save_state.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QTextStream in(&file);
	QString line;
	// -------------------- active skin
	line = in.readLine();
	skin = line;
	// -------------------- skin list
	line = in.readLine();
	unlockedSkins = line.split(' ');
	// -------------------- number of unlocked levels
	line = in.readLine();
	startingLvl = line.toInt();
	// -------------------- push mode
	line = in.readLine();
	pushMode = (bool)line.toInt();
	// -------------------- pull mode
	line = in.readLine();
	pullMode = (bool)line.toInt();

	file.close();
}

QPixmap UserProfile::getTex(QString tex) {
	QString path = "../texture/" + skin + "/" + tex + ".png";
	QPixmap texture = QPixmap(path);
	if (texture.isNull()) { // failsafe to default texture
		path = "../texture/default/" + tex + ".png";
		return QPixmap(path);
	}
	return texture;
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
bool UserProfile::autoPush() {
	return pushMode;
}
void UserProfile::setPushMode(bool mode) {
	pushMode = mode;
}
bool UserProfile::autoPull() {
	return pullMode;
}
void UserProfile::setPullMode(bool mode) {
	pullMode = mode;
}