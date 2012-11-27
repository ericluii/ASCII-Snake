/*
 Link.cpp - link of snake class
 By: Eric Lui

 Changelog:
 	27/11/12 EL - Version 1.0.0 complete, and added documentation

 Notes:
 	27/11/12 EL - refer to food.cpp and snake.cpp for changes(affects game implementaion)
	27/11/12 EL - change direction = char to an enumeration

 If you use this code, please credit me. However, this is free to use.
 */
#include "link.h"
#include <iostream>

using namespace std;

// Constructor for link
//		+ x and y are the coordinates of the link
//		+ direction is the initial direction the link
//		  should go
Link::Link(int x, int y, char direction): x(x), y(y), direction(direction), lastDirection(direction) {}

// Link::changeDirection(char direction)
//		+ Accepts a char representation of a direction
//		- Changes the direction of the link
void Link::changeDirection(char direction) {
	lastDirection = this->direction;
	this->direction = direction;
}

// Link::moveLink(char direction)
//		+ Accepts a char representation of a direction
//		- Moves the link based on this->direction
//		- Sets this->direction to direction
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

// Link::operator==(const Link &link)
//		+ Accepts a link
//		- Returns true if all the fields are equal
bool Link::operator==(const Link &link) const {
	if (x == link.x && y == link.y) {
		return true;
	}
	else {
		return false;
	}
}

// Link::operator=(const Link &link)
//		+ Accepts a link
//		- Sets (*this) fields to be the same as link
Link& Link::operator=(const Link &link) {
	x = link.getX();
	y = link.getY();
	direction = link.getDirection();
	lastDirection = link.getLastDirection();

	return (*this);
}

// Link::getX()
//		- Returns the x-coordinate of link
int Link::getX() const {
	return x;
}

// Link::getY()
//		- Returns the y-coordinate of link
int Link::getY() const {
	return y;
}

// Link::getDirection()
//		- Returns the direction of the link
char Link::getDirection() const {
	return direction;
}

// Link::getLastDirection()
//		- Returns the direction of the last direction
char Link::getLastDirection() const {
	return lastDirection;
}
