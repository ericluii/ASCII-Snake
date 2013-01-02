#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <vector>
#include "food.h"
#include "link.h"

class Snake {
	private:
		int speed;
		std::vector<Link> body;
		char lastDirection;
	public:
		Snake(int x, int y, int length);
		void setDirection(char direction);
		bool moveSnake(std::vector<Food> &prey);
		void growSnake();
		int length() const;
		int linkPosX(int);
		int linkPosY(int);
		int getSpeed();
		void increaseSpeed();
		bool checkOverlap(int x, int y);
};

#endif
