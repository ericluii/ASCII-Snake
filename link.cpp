#include "link.h"
#include <iostream>

using namespace std;

Link::Link(int x, int y, char direction):
	x(x),
	y(y),
	direction(direction),
	lastDirection(direction)
{}

void Link::changeDirection(char direction) {
	lastDirection = this->direction;
	this->direction = direction;
}

void Link::moveLink(char direction) {
	switch (this->direction) {
		case 'u':
			y--;
			break;
		case 'd':
			y++;
			break;
		case 'l':
			x--;
			break;
		case 'r':
			x++;
			break;
	}
	lastDirection = this->direction;
	this->direction = direction;
}

bool Link::operator==(const Link &link) const {
	if (x == link.x && y == link.y) {
		return true;
	}
	else {
		return false;
	}
}

Link& Link::operator=(const Link &link) {
	x = link.getX();
	y = link.getY();
	direction = link.getDirection();
	lastDirection = link.getLastDirection();

	return (*this);
}

int Link::getX() const {
	return x;
}

int Link::getY() const {
	return y;
}

char Link::getDirection() const {
	return direction;
}

char Link::getLastDirection() const {
	return lastDirection;
}
