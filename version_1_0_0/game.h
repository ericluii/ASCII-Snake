#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <vector>
#include "food.h"
#include "snake.h"

class Game {
	private:
		int width;
		int height;
		int points;
		int highscore;
		std::vector< std::vector<char> > board;
		std::vector<Food> prey;
		Snake snake;
	public:
		Game(int width, int height);
		Game(int width, int height, int snakeLength, int preyLength);
		void newGame();
		bool updateGame();
		void updateSnake(char direction);
		void addFood();
		void printGame() const;
		int gameSpeed();
		bool setHighscore();
};

#endif
