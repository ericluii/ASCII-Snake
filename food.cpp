/*
 food.cpp - food for snake class
 By: Eric Lui

 Changelog:
 	27/11/12 EL - Version 1.0.0 complete, and added documentation

 Notes:
 	27/11/12 EL - Can be completely reimplemented
				- A food container which follows the composite design structure
				- Food types inherit from food base class(bad food and good food)

 If you use this code, please credit me. However, this is free to use.
 */

#include "food.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std;

// Constructor for a food
//		+ x and y are coordinates, and type is the type of food
//			- 0 is good food and 1 is bad food
//		- Each food has a randomized lifespan
Food::Food(int x, int y, int type): x(x), y(y), type(type) {
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

// Food:getX()
//		- Returns the x coordinate of food
int Food::getX() {
	return x;
}

// Food::getY()
//		- Returns the y coordinate of food
int Food::getY() {
	return y;
}

// Food::getType()
//		- Returns the type of the food
int Food::getType() {
	return type;
}

// Food::getLifespan()
//		- Decreases the lifespan by 1
//		- Returns the lifespan
int Food::getLifespan() {
	lifespan--;
	return lifespan;
}

// Food::changeFoodType(int type)
//		- Changes the type of the food
//		- Returns the old food type
int Food::changeFoodType(int type) {
	int temp = this->type;
	this->type = type;
	return temp;
}

// Food::changeLifespan(int time)
//		- Changes lifespan to time
void Food::changeLifespan(int time) {
	lifespan = time;
}

// Food::containsTwoEatableFood(vector<Food> prey)
//		+ Accepts a vector of food, prey
//		- Returns true if there are atleast two
//		   "good" foods in the game
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

// Food::checkFoodPosition(vector<Food> prey, int x, int y)
//		+ Accepts a coordinate and a vector of food, x, y, and prey
//		- Returns true if there is food at that position
bool checkFoodPosition(vector<Food> prey, int x, int y) {
	for (int i = 0; i < prey.size(); i++) {
		if (prey[i].getX() == x && prey[i].getY() == y)
			return true;
	}

	return false;
}
