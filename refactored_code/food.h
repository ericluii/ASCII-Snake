#ifndef _food_h_
#define _food_h_
class Snake;
#include "coordinate.h"

class Food {
	public:
        enum FoodType {addPoint, minusThreePoints, decreaseSpeed, increaseSpeed, decreaseLength, increaseLength, TOTAL_TYPES};
		Food(int x, int y, FoodType type);
		Coordinate position();
        char displayCharacter();
		FoodType getType();
		int getLifespan();
		void changeLifespan(int time);
        int hasBeenEatenBy(Snake& aSnake);
	private:
        Coordinate coor;
		FoodType type;
		int lifespan;
        char display;
};

#endif
