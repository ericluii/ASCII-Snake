/*
 Snake.cpp - snake class
 By: Eric Lui

 Changelog:
 	27/11/12 EL - Version 1.0.0 complete, and added documentation

 Notes:
 	27/11/12 EL - Snake::setDirection can move some code to Link::changeDirection
	27/11/12 EL - Can reimplement and have snake inherit vector class

 If you use this code, please credit me. However, this is free to use.
 */

#include <iostream>
#include <vector>
#include "link.h"
#include "snake.h"
#include "food.h"

using namespace std;

// Snake Constructor
//		+ x and y are the starting coordinates
//		+ length is the starting length
//		- base speed is 20, the lower the faster.
Snake::Snake(int x, int y, int length):speed(20), body() {
	// For loop creates body of size 'length'
	for( int i = 0; i < length; i++) {
		body.push_back(Link(x + i, y, 'l'));
	}
}

// Snake::setDirection(char direction)
//		+ accepts a character which represents the direction
//		   that the snake should go
void Snake::setDirection(char direction) {
	switch(body.at(0).getDirection()) {
		case 'l':
			if (direction != 'r') {	
				body.at(0).changeDirection(direction);
			}
			break;
		case 'r':
			if (direction != 'l') {	
				body.at(0).changeDirection(direction);
			}
			break;
		case 'u':
			if (direction != 'd') {	
				body.at(0).changeDirection(direction);
			}
			break;
		case 'd':
			if (direction != 'u') {	
				body.at(0).changeDirection(direction);
			}
			break;
	}
}

// Snake::moveSnake(vector<food> &prey)
//		+ Accepts a vector of food
//		- Moves snake according to the set direction
//		- If snake tail is at the same position of a food
//		   grow the snake, and delete food
//		- Returns true if snake makes a valid move (not gameover)
bool Snake::moveSnake(vector<Food> &prey) {
	Link nextLink = Link(body.at(0).getX(),
		body.at(0).getY(), body.at(0).getDirection());
	
	nextLink.moveLink(nextLink.getDirection());

	// Checks to see if head is going into its' own body
	for( int i = 0; i < body.size(); i++) {
		if (body.at(i) == nextLink) {
			return false;
		}
	}

	// Moves entire snake
	for( int i = 0; i < body.size(); i++) {
		if (i == 0) {
			body.at(i).moveLink(body.at(i).getDirection());
		}
		else {
			body.at(i).moveLink(body.at(i - 1).getLastDirection());
		}
	}

	// Checks if snake should be resized
	for(int i = 0; i < prey.size(); i++) {
		if(prey.at(i).getX() == body.at(body.size() - 1).getX() &&
			prey.at(i).getY() == body.at(body.size() - 1).getY()) {
			growSnake();
			prey.erase(prey.begin() + i);
		}
	}

	return true;
}

// Snake::growSnake()
//		- Increases the size of the snake
void Snake::growSnake() {
	Link lastLink = body.at(body.size() - 1);

	switch(lastLink.getLastDirection()) {
		case 'l':
			body.push_back(Link(lastLink.getX() + 1, lastLink.getY(), lastLink.getLastDirection()));
			break;
		case 'r':
			body.push_back(Link(lastLink.getX() - 1, lastLink.getY(), lastLink.getLastDirection()));
			break;
		case 'd':
			body.push_back(Link(lastLink.getX(), lastLink.getY() - 1, lastLink.getLastDirection()));
			break;
		case 'u':
			body.push_back(Link(lastLink.getX(), lastLink.getY() + 1, lastLink.getLastDirection()));
			break;
	}
}

// Snake::length()
//		- Returns the length of the snake
int Snake::length() const{
	return body.size();
}

// Snake::linkPosX(int bodyPart)
//		- Returns the x coordinate of the link at index
//		   bodyPart
int Snake::linkPosX(int bodyPart) {
	return body.at(bodyPart).getX();
}

// Snake::linkPosY(int bodyPart)
//		- Return the y coordinate of the link at index
//		   bodyPart
int Snake::linkPosY(int bodyPart) {
	return body.at(bodyPart).getY();
}

// Snake::getSPeed()
//		- Returns the snake speed
int Snake::getSpeed() {
	return speed;
}

// Snake::increaseSpeed()
//		- Increases the snake speed
void Snake::increaseSpeed() {
	if (speed > 0)
		speed--;
}

// Snake::checkOverlap(int x, int y)
//		+ Accepts coordinates x and y
//		- Returns true if the snake is on top
//		   of that coordinate
bool Snake::checkOverlap(int x, int y) {
	for (int i = 0; i < body.size(); i++) {
		if (body.at(i).getX() == x && body.at(i).getY() == y) {
			return true;
		}
	}

	return false;
}
