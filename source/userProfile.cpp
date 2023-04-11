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
void UserProfile::writeSaveState() {
	QFile file("../configs/save_state.txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}
	QTextStream out(&file);
	out << skin << "\n";
	out << unlockedSkins.join(' ') << "\n";
	out << unlockedLvlNb << "\n";
	out << pushMode << "\n";
	out << pullMode << "\n";

	file.close();
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
	unlockedLvlNb = line.toInt();
	// -------------------- push mode
	line = in.readLine();
	pushMode = (bool)line.toInt();
	// -------------------- pull mode
	line = in.readLine();
	pullMode = (bool)line.toInt();

	file.close();
}

void UserProfile::loadSkinList(QStringList& returnList) {
	QFile file("../configs/skin_list.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}
	QTextStream in(&file);
	QString line = in.readLine();
	while (line.length() > 1) {
		returnList.append(line);
		line = in.readLine();
	}

	file.close();
}
QString UserProfile::unlockNewSkin(int seed) {

	QStringList skinList;
	loadSkinList(skinList);
	if (unlockedSkins.size() >= skinList.size()) {
		return QString(""); // no more skin to unlock
	}
	for (QString givenSkin : unlockedSkins) {
		skinList.remove(skinList.indexOf(givenSkin));
	}

	// [seed] is generated by the captor
	QString newSkin = skinList.at(seed % skinList.size());
	unlockedSkins.append(newSkin); // add new skin to unlocked list
	skin = newSkin; // switch to new skin
	return newSkin;
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

QString UserProfile::changeSkin(int dir) {
	if (dir == 0) return skin;
	int skinIndex = unlockedSkins.indexOf(skin);
	skinIndex = (skinIndex + dir) % unlockedSkins.size();
	if (skinIndex < 0) skinIndex = unlockedSkins.size() - 1;
	skin = unlockedSkins[skinIndex];
	return skin;
}

