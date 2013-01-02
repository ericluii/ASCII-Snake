/*
 game.cpp - game of snake class
 By: Eric Lui

 Changelog:
 	27/11/12 EL - Version 1.0.0 complete, and added documentation

 Notes:
 	27/11/12 EL - refer to food.cpp and snake.cpp for changes(affects game implementaion)
	27/11/12 EL - Maybe add a pointer to a board to all other class types so that each class can individually update the board and it doesn't have to be cleared recreated each refresh.

 If you use this code, please credit me. However, this is free to use.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include "game.h"
#include "snake.h"
#include "food.h"

using namespace std;

// Constructor for a game
//		+ Accepts a width and height for game board
Game::Game(int width, int height): width(width), height(height), points(0), highscore(0),
									board(width, vector<char>(height)), prey(), snake(width/2, height/2, 5) {
	// Loads highscore from file
	ifstream highscoreText("stats");
	highscoreText >> highscore;
	highscoreText.close();

	// Sets board values(empty board)
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			board[i][j] = ' ';
		}
	}
	
	// Draws snake to board
	for(int i = 0; i < snake.length(); i++) {
		board[snake.linkPosX(i)][snake.linkPosY(i)] = '@';
	}

	// Adds food to game
	addFood();
	addFood();
}

// Game::newGame()
//		- Resets game to default values
void Game::newGame() {
	// Resets points
	points = 0;

	// Resets snake
	snake = Snake(width/2, height/2, 5);

	// Clears board
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			board[i][j] = ' ';
		}
	}

	// Adds snake to board
	for(int i = 0; i < snake.length(); i++) {
		board[snake.linkPosX(i)][snake.linkPosY(i)] = '@';
	}

	// Clears food
	prey.clear();

	// Adds food to game
	addFood();
	addFood();
}

// Game::updateGame()
//		- Moves snake
//		- If snake eats food, increase/decrease points and
//		   if points is divisible by 5 increase speed
//		- Returns true if game is not over
bool Game::updateGame() {
	// Move snake, and return false if invalid move
	if(!snake.moveSnake(prey)) {
		return false;
	}

	// Clear board
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			board[i][j] = ' ';
		}
	}

	// Add food to board
	for(int i = 0; i < prey.size(); i++) {
		if (prey.at(i).getType() == 0) {
			board[prey.at(i).getX()][prey.at(i).getY()] = '+';
		}
		else if (prey.at(i).getType() == 1) {
			board[prey.at(i).getX()][prey.at(i).getY()] = 'x';
		}
		// If head is at food, increment points and maybe increase speed
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
		// If lifespan of food is over, remove food and draw new food
		else if (prey.at(i).getType() == 1 && prey.at(i).getLifespan() == 0) {
			prey.erase(prey.begin() + i);
			addFood();
		}
	}

	// Add snake to board
	for(int i = 0; i < snake.length(); i++) {
		// Check to see if snake is outside of bounds of board
		// if so return false
		if (snake.linkPosX(i) < 0 || snake.linkPosX(i) >= width ||
			snake.linkPosY(i) < 0 || snake.linkPosY(i) >= height) {
			return false;
		}

		board[snake.linkPosX(i)][snake.linkPosY(i)] = '@';
	}

	return true;
}

// Game::updateSnake(char direction)
//		+ Accepts a char representation of a direction
//		- sets the snake direction
void Game::updateSnake(char direction) {
	snake.setDirection(direction);
}

// Game::addFood()
//		- Adds a new food to the game at a position
//		   which is not being used by other food or snake
void Game::addFood() {
	int type = 0;
	int x = rand() % width; 
	int y = rand() % height;

	// If game contains food which is good for you
	// Allow the possibility of bad food being generated
	if (containsTwoEatableFood(prey)) {
		type = rand() % 2;	
	}

	// Keep finding coordinates until coordinates do not overlap
	// with food or snake
	while(snake.checkOverlap(x, y) || checkFoodPosition(prey,x , y)) {
		x = rand() % width;
		y = rand() % height;
	}

	// add food
	prey.push_back(Food(x, y, type));

	// add food to board
	if (type == 0) {
		board[x][y] = '+';
	}
	else if (type == 1) {
		board[x][y] = 'x';
	}
}

// Game::printGame()
//		- Prints gameboard to standard output
void Game::printGame() const {
	// Clears screen
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

// Game::gameSpeed()
//		- Returns the speed of the snake
int Game::gameSpeed() {
	return snake.getSpeed();
}

// Game::setHighscore()
//		- Sets the highscore of the game
//		  if the points are greater than the
//		  current highscore
//		- Returns true if a highscore was set
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
