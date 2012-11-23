#include <iostream>
#include <vector>
#include "link.h"
#include "snake.h"
#include "food.h"

using namespace std;

Snake::Snake(int x, int y, int length):
	speed(20),
	body()
{
	for( int i = 0; i < length; i++) {
		body.push_back(Link(x + i, y, 'l'));
	}
}

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

bool Snake::moveSnake(vector<Food> &prey) {
	Link nextLink = Link(body.at(0).getX(),
		body.at(0).getY(), body.at(0).getDirection());
	
	nextLink.moveLink(nextLink.getDirection());

	for( int i = 0; i < body.size(); i++) {
		if (body.at(i) == nextLink) {
			return false;
		}
	}

	for( int i = 0; i < body.size(); i++) {
		if (i == 0) {
			body.at(i).moveLink(body.at(i).getDirection());
		}
		else {
			body.at(i).moveLink(body.at(i - 1).getLastDirection());
		}
	}

	for(int i = 0; i < prey.size(); i++) {
		if(prey.at(i).getX() == body.at(body.size() - 1).getX() &&
			prey.at(i).getY() == body.at(body.size() - 1).getY()) {
			growSnake();
			prey.erase(prey.begin() + i);
		}
	}

	return true;
}

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

int Snake::length() const{
	return body.size();
}

int Snake::linkPosX(int bodyPart) {
	return body.at(bodyPart).getX();
}

int Snake::linkPosY(int bodyPart) {
	return body.at(bodyPart).getY();
}

int Snake::getSpeed() {
	return speed;
}

void Snake::increaseSpeed() {
	if (speed > 0)
		speed--;
}

bool Snake::checkOverlap(int x, int y) {
	for (int i = 0; i < body.size(); i++) {
		if (body.at(i).getX() == x && body.at(i).getY() == y) {
			return true;
		}
	}

	return false;
}

void Snake::debug() const{
	cout << "body: " << body.size() << endl;
	cout << "speed: " << speed << endl;
}
