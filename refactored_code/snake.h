#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <vector>
#include "foodContainer.h"
#include "link.h"

class Snake {
	private:
		std::vector<Link> body;
		char lastDirection;
	public:
		Snake(int x, int y, int length);
        int speed;
		void setDirection(char direction);
		bool moveSnake(FoodContainer& prey);
		void growSnake();
        void shrinkSnake();
		int length() const;
		int linkPosX(int);
		int linkPosY(int);
		void increaseSpeed();
		bool checkOverlap(int x, int y);
};

#endif
