#ifndef __FOOD_H__
#define __FOOD_H__
#include <vector>

class Food {
	public:
		Food(int x, int y, int type);
		int getX();
		int getY();
		int getType();
		int getLifespan();
		int changeFoodType(int type);
		void changeLifespan(int time);
	private:
		int x;
		int y;
		int type;
		int lifespan;
};

bool containsTwoEatableFood(std::vector<Food> prey);
bool checkFoodPosition(std::vector<Food> prey, int x, int y);

#endif
