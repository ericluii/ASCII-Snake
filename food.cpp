#include "food.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std;

Food::Food(int x, int y, int type):
	x(x),
	y(y),
	type(type)
{
	int random = rand() % 3;
	if (random == 0) {
		lifespan = 31;
	}
	else if (random == 1) {
		lifespan = 43;
	}
	else {
		lifespan = 51;
	}
}

int Food::getX() {
	return x;
}

int Food::getY() {
	return y;
}

int Food::getType() {
	return type;
}

int Food::getLifespan() {
	lifespan--;
	return lifespan;
}

int Food::changeFoodType(int type) {
	int temp = this->type;
	this->type = type;
	return temp;
}

void Food::changeLifespan(int time) {
	lifespan = time;
}

bool containsTwoEatableFood(vector<Food> prey) {
	int totalEatable = 0;

	for (int i = 0; i < prey.size(); i++) {
		if (prey[i].getType() == 0) {
			totalEatable++;
			if (totalEatable == 2)
				return true;
		}
	}

	return false;
}

bool checkFoodPosition(vector<Food> prey, int x, int y) {
	for (int i = 0; i < prey.size(); i++) {
		if (prey[i].getX() == x && prey[i].getY() == y)
			return true;
	}

	return false;
}
