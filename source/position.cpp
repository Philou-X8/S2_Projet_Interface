#include "position.h"

Coords::Coords() {
	x = 0;
	y = 0;
}
Coords::Coords(int xx, int yy) {
	x = xx;
	y = yy;
}

Coords::Coords(const Coords& p2) {
	x = p2.x;
	y = p2.y;
}

bool Coords::setPos(const int xx, const int yy) {
	x = xx;
	y = yy;
	return true;
}
bool Coords::setPos(const Coords& p2) {
	return setPos(p2.x, p2.y);
}
bool Coords::move(const int dx, const int dy) {
	x += dx;
	y += dy;
	return true;
}
bool Coords::move(const Coords& delta) {
	move(delta.x, delta.y);
	return true;
}

bool Coords::operator==(const Coords& p2) {
	bool equal = true;
	if (x != p2.x) equal = false;
	if (y != p2.y) equal = false;
	return equal;
}
bool Coords::operator!=(const Coords& p2) {
	if (x != p2.x) return true;
	if (y != p2.y) return true;
	return false;
}

Coords& Coords::operator=(const Coords& p2) {
	x = p2.x;
	y = p2.y;
	return *this;
}
/*
PlayerPos& PlayerPos::operator=(const PlayerPos* p2) {
	setPos(*p2);
	return *this;
}
*/
Coords& Coords::operator+=(const Coords& p2) {
	move(p2);
	return *this;
}
Coords& Coords::operator-=(const Coords& p2) {
	move(-p2.x, -p2.y);
	return *this;
}
Coords Coords::operator+(const Coords& p2) {
	Coords total(x + p2.x, y + p2.y);
	return total;
}
Coords Coords::operator-(const Coords& p2) {
	Coords total(x - p2.x, y - p2.y);
	return total;
}

int clampM(int& val) {
	if (val < 0) {
		val = 0;
		return val;
	}
	if (val > 19) {
		val = 19;
		return val;
	}
	return val;
}
int clampM(const int& val) {
	if (val < 0) {
		return 0;
	}
	if (val > 19) {
		return 19;
	}
	return val;
}

Coords clampP(Coords& pos) {
	clampM(pos.x);
	clampM(pos.y);
	return pos;
}