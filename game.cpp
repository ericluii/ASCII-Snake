#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include "game.h"
#include "snake.h"
#include "food.h"

using namespace std;

Game::Game(int width, int height):
	width(width),
	height(height),
	points(0),
	highscore(0),
	board(width, vector<char>(height)),
	prey(),
	snake(width/2, height/2, 5)
{
	ifstream highscoreText("stats");
	highscoreText >> highscore;
	highscoreText.close();

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			board[i][j] = ' ';
		}
	}
	
	for(int i = 0; i < snake.length(); i++) {
		board[snake.linkPosX(i)][snake.linkPosY(i)] = '@';
	}

	addFood();
	addFood();
}

Game::Game(int width, int height, int snakeLength, int preyLength):
	width(width),
	height(height),
	points(0),
	highscore(0),
	board(width, vector<char>(height)),
	prey(),
	snake(width/2, height/2, snakeLength)
{
	ifstream highscoreText("stats");
	highscoreText >> highscore;
	highscoreText.close();

	for(int i = 0; i < preyLength; i++) {
		addFood();
	}
}

void Game::newGame() {
	points = 0;

	snake = Snake(width/2, height/2, 5);

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			board[i][j] = ' ';
		}
	}

	for(int i = 0; i < snake.length(); i++) {
		board[snake.linkPosX(i)][snake.linkPosY(i)] = '@';
	}

	prey.clear();

	addFood();
	addFood();
}

bool Game::updateGame() {
	if(!snake.moveSnake(prey)) {
		return false;
	}

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			board[i][j] = ' ';
		}
	}

	for(int i = 0; i < prey.size(); i++) {
		if (prey.at(i).getType() == 0) {
			board[prey.at(i).getX()][prey.at(i).getY()] = '+';
		}
		else if (prey.at(i).getType() == 1) {
			board[prey.at(i).getX()][prey.at(i).getY()] = 'x';
		}
		if (snake.linkPosX(0) == prey.at(i).getX() && snake.linkPosY(0) == prey.at(i).getY()) {
			addFood();
			prey.at(i).changeLifespan(snake.length() + 1);
			if (prey.at(i).getType() == 0) {
				if (points == highscore) {
					highscore++;
				}
				points++;
			}
			else if (prey.at(i).getType() == 1) {
				points = points - 3;
			}
			if (points % 5 == 0) {
				snake.increaseSpeed();
			}
		}
		else if (prey.at(i).getType() == 1 && prey.at(i).getLifespan() == 0) {
			prey.erase(prey.begin() + i);
			addFood();
		}
	}

	for(int i = 0; i < snake.length(); i++) {
		if (snake.linkPosX(i) < 0 || snake.linkPosX(i) >= width ||
			snake.linkPosY(i) < 0 || snake.linkPosY(i) >= height) {
			return false;
		}

		board[snake.linkPosX(i)][snake.linkPosY(i)] = '@';
	}

	return true;
}

void Game::updateSnake(char direction) {
	snake.setDirection(direction);
}

void Game::addFood() {
	int type = 0;
	int x = rand() % width; 
	int y = rand() % height;

	if (containsTwoEatableFood(prey)) {
		type = rand() % 2;	
	}

	while(snake.checkOverlap(x, y) || checkFoodPosition(prey,x , y)) {
		x = rand() % width;
		y = rand() % height;
	}

	prey.push_back(Food(x, y, type));

	if (type == 0) {
		board[x][y] = '+';
	}
	else if (type == 1) {
		board[x][y] = 'x';
	}
}

void Game::printGame() const {
	cout << "\033[2J\033[1;1H";

	cout << '|';
	for(int i = 0; i < width ; i++) {
		cout << "\\";
		if (i != width - 1) {
			cout << " ";
		}
	}
	cout << '|' << endl;
	for(int i = 0; i < height; i++) {
		cout << '|';
		for(int j = 0; j < width; j++) {
			if (j != width - 1) {
				cout << board[j][i] << " ";
			}
			else {
				cout << board[j][i];
			}
		}
		cout << '|' << endl;
	}

	cout << '|';
	for(int i = 0; i < width; i++) {
		cout << "/";
		if (i != width - 1) {
			cout << " ";
		}
	}
	cout << '|';
	cout << endl;
	cout << "Points: " << points << "\tHighscore: " << highscore << endl;
}

int Game::gameSpeed() {
	return snake.getSpeed();
}

bool Game::setHighscore() {
	if (points >= highscore) {
		highscore = points;

		ofstream highscoreText("stats");
		highscoreText << points;
		highscoreText.close();
		return true;
	}
	
	return false;
}

void Game::saveGame() const{
	debug();
	ofstream ofs("gameSave.snk");
	ofs.write((char *)this, sizeof((*this)));
	ofs.close();
}

void Game::debug() const {
	 cout << "width: "  << width << endl;
	 cout << "board-width: "  << board.size() << endl;
	 cout << "height: " << height << endl;
	 cout << "board-height: " << board[0].size() << endl;
	 cout << "points: " << points << endl;
	 cout << "highscore: " << highscore << endl;
	 cout << "prey: " << prey.size() << endl;
	 cout << "snake: " << snake.length() << endl;
	 snake.debug();
}
