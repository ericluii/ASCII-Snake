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
#include "snake.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

// Constructor for a food
//		+ x and y are coordinates, and type is the type of food
//			- 0 is good food and 1 is bad food
//		- Each food has a randomized lifespan
Food::Food(int x, int y, FoodType type): coor(x, y), type(type) {
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
    
    switch(type) {
        case addPoint:
            display = '+';
            break;
        case minusThreePoints:
            display = '-';
            break;
        case increaseSpeed:
            display = 'f';
            break;
        case decreaseSpeed:
            display = 's';
            break;
        case increaseLength:
            display = 'l';
            break;
        case decreaseLength:
            display = 'd';
            break;
    }
}

Coordinate Food::position() {
    return coor;
}

char Food::displayCharacter() {
    return display;
}

// Food::getType()
//		- Returns the type of the food
Food::FoodType Food::getType() {
	return type;
}

// Food::getLifespan()
//		- Decreases the lifespan by 1
//		- Returns the lifespan
int Food::getLifespan() {
	lifespan--;
	return lifespan;
}

// Food::changeLifespan(int time)
//		- Changes lifespan to time
void Food::changeLifespan(int time) {
	lifespan = time;
}

int Food::hasBeenEatenBy(Snake& aSnake) {
    switch(type) {
        case addPoint:
            return 1;
            break;
        case minusThreePoints:
            return -3;
            break;
        case increaseSpeed:
            if (aSnake.speed > 1) {
                aSnake.speed--;
            }
            break;
        case decreaseSpeed:
            aSnake.speed++;
            break;
        case increaseLength:
            aSnake.growSnake();
            break;
        case decreaseLength:
            aSnake.shrinkSnake();
            break;
    }
    
    return 1;
}