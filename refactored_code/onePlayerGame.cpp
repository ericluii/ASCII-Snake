#include "onePlayerGame.h"
#include "game.h"
#include "snake.h"
#include "food.h"
#include <iostream>
#include <fstream>

using namespace std;

// The following section below is used to allow
// key press events in a terminal window
int khit (void) {
	struct timeval tv;
	fd_set rdfs;
    
	tv.tv_sec = 0;
	tv.tv_usec = 0;
    
	FD_ZERO(&rdfs);
	FD_SET (STDIN_FILENO, &rdfs);
    
	select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &rdfs);
}

onePlayerGame::onePlayerGame(int width, int height, int snakeLength):
    Game(width, height), score(0), highscore(0), snake(width/2, height/2, 5) {
        // Loads highscore from file
        ifstream highscoreText("stats");
        highscoreText >> highscore;
        highscoreText.close();
        
        // Draws snake to board
        for(int i = 0; i < snake.length(); i++) {
            board[snake.linkPosX(i)][snake.linkPosY(i)] = '@';
        }
        
        addFood();
        addFood();
}

void onePlayerGame::newGame() {
    // Reset score
    score = 0;
    
    // Reset Snake
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
    
    // Resets Food
    prey.clear();
    addFood();
    addFood();
}

void onePlayerGame::playGame() {
    char direction;
	while(true) {
		if (khit()) {
			direction = getchar();
			if (direction == 'w')
				snake.setDirection('u');
			else if (direction == 'a')
				snake.setDirection('l');
			else if (direction == 's')
				snake.setDirection('d');
			else if (direction == 'd')
				snake.setDirection('r');
			else if (direction == ' ' || direction == 'p')
				pauseGame();
		}
		printGame();
		if(!updateGame()) {
			break;
		}
		usleep(snakeSpeed()[0] * 5000);
	}
}

bool onePlayerGame::updateGame() {
    board[snake.linkPosX(snake.length() - 1)][snake.linkPosY(snake.length() - 1)] = ' ';
    
    // Moves snake and returns false if the move is invalid
    if (!snake.moveSnake(prey)) {
        return false;
    }
    
	for(int i = 0; i < prey.size(); i++) {
		// If head is at food, increment score and maybe increase speed
		if (snake.linkPosX(0) == prey.at(i).getX() && snake.linkPosY(0) == prey.at(i).getY()) {
			addFood();
			prey.at(i).changeLifespan(snake.length() + 1);
			if (prey.at(i).getType() == 0) {
				if (score == highscore) {
					highscore++;
				}
				score++;
			}
			else if (prey.at(i).getType() == 1) {
				score = score - 3;
			}
			if (score % 5 == 0) {
				snake.increaseSpeed();
			}
		}
		// If lifespan of food is over, remove food and draw new food
		else if (prey.at(i).getType() == 1 && prey.at(i).getLifespan() == 0) {
            board[prey.at(i).getX()][prey.at(i).getY()] = ' ';
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
	}
    
    board[snake.linkPosX(0)][snake.linkPosY(0)] = '@';
    board[snake.linkPosX(snake.length() - 1)][snake.linkPosY(snake.length() - 1)] = '@';
}

void onePlayerGame::printGame() const {
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
	cout << "Score: " << score << "\tHighscore: " << highscore << endl;
}

int* onePlayerGame::snakeSpeed() {
    int* speeds = new int[1];
    
    speeds[0] = snake.getSpeed();
    
    return speeds;
}

void onePlayerGame::addFood() {
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

bool onePlayerGame::setHighscore() {
	if (score >= highscore) {
		highscore = score;
        
		ofstream highscoreText("stats");
		highscoreText << score;
		highscoreText.close();
		return true;
	}
	
	return false;
}