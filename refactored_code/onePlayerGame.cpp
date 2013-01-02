#include "onePlayerGame.h"
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
    prey.removeAllFood();
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
    
    board[snake.linkPosX(0)][snake.linkPosY(0)] = '@';
 
	for(int i = 0; i < prey.amountOfFood(); i++) {
		// If head is at food, increment score and maybe increase speed
		if (snake.linkPosX(0) == prey.getFood(i)->position().x && snake.linkPosY(0) == prey.getFood(i)->position().y) {
			addFood();
			prey.getFood(i)->changeLifespan(snake.length() + 1);
            board[snake.linkPosX(snake.length() - 1)][snake.linkPosY(snake.length() - 1)] = ' ';
			score += prey.getFood(i)->hasBeenEatenBy(snake);
            if (score < 0) {
                score = 0;
            }
            board[snake.linkPosX(snake.length() - 1)][snake.linkPosY(snake.length() - 1)] = '@';
		}
		// If lifespan of food is over, remove food and draw new food
		else if (prey.getFood(i)->getLifespan() == 0) {
            board[prey.getFood(i)->position().x][prey.getFood(i)->position().y] = ' ';
			prey.removeFood(prey.getFood(i));
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
    
    speeds[0] = snake.speed;
    
    return speeds;
}

void onePlayerGame::addFood() {
    Food::FoodType type;
    
    srand(time(NULL));
    
    if (prey.containsHelpfulFood()) {
        type = static_cast<Food::FoodType>(rand() % Food::TOTAL_TYPES);
    }
    else {
        type = static_cast<Food::FoodType>((rand() % (Food::TOTAL_TYPES/2)) * 2);
    }
    
	int x = rand() % width;
	int y = rand() % height;
    
	// Keep finding coordinates until coordinates do not overlap
	// with food or snake
    Food* newFood = new Food(x, y, type);
    
	while(snake.checkOverlap(x, y) || !prey.addFood(newFood)) {
		x = rand() % width;
		y = rand() % height;
        newFood = new Food(x, y, type);
	}
    
	// add food to board
	board[x][y] = newFood->displayCharacter();
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