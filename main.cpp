/*
 main.cpp - main method of snake
 By: Eric Lui

 Changelog:
 	27/11/12 EL - Version 1.0.0 complete, and added documentation

 Notes:
 	27/11/12 EL - refer to food.cpp and snake.cpp for changes(affects game implementaion)
	27/11/12 EL - Implement a save and load game option
	27/11/12 EL - Plans to make main menu dynamic and allow settings

 If you use this code, please credit me. However, this is free to use.
 */

#include "game.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
using namespace std;

// The following section below is used to allow
// key press events in a terminal window
void changemode(int dir) {
	static struct termios oldt, newt;

	if ( dir == 1 ) {
		tcgetattr( STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~( ICANON | ECHO );
		tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	}
	else {
		tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	}
}

// The following section below is used to allow
// key press events in a terminal window
int kbhit (void) {
	struct timeval tv;
	fd_set rdfs;

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	FD_ZERO(&rdfs);
	FD_SET (STDIN_FILENO, &rdfs);

	select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &rdfs);
}

// pausGame(const Game &currentGame)
//		- Places game in an inifite loop to pause
//		- unpauses by pressing p or space, and q to quit
void pauseGame(const Game &currentGame) {
	cout << "\t\tGAME PAUSED - P/SPACE TO RESUME - Q TO QUIT" << endl;
	char command;

	while(true) {
		if (kbhit()) {
			command = getchar();
			if (command == ' ' || command == 'p') {
				break;
			}
			else if (command = 'q') {
				//currentGame.saveGame();
				exit(0);
			}
		}
	}
}

// mainMenu(Game &currentGame)
//		- Places game in an infinite loop to display menu
//		- starts game on any key press
void mainMenu(Game &currentGame) {
	char command;
	cout << "\033[2J\033[1;1H";

	cout << "|";
	for (int i = 0; i < 39; i++)
		cout << "\\ ";
	cout << "\\|" << endl;
	cout << "|                                                                          By:EL|" << endl;
	cout << "|          SSSSSSSSSS  NN      NN  AAAAAAAAAA  KK      KK  EEEEEEEEEE           |" << endl;
	cout << "|          SSSSSSSSSS  NNN     NN  AAAAAAAAAA  KK     KK   EEEEEEEEEE           |" << endl;
	cout << "|          SS          NNNN    NN  AA      AA  KK    KK    EE                   |" << endl;
	cout << "|          SS          NN NN   NN  AA      AA  KK   KK     EE                   |" << endl;
	cout << "|          SSSSSSSSSS  NN  NN  NN  AAAAAAAAAA  KKKKK       EEEEEEEEEE           |" << endl;
	cout << "|          SSSSSSSSSS  NN  NN  NN  AAAAAAAAAA  KKKKK       EEEEEEEEEE           |" << endl;
	cout << "|                  SS  NN   NN NN  AA      AA  KK   KK     EE                   |" << endl;
	cout << "|                  SS  NN    NNNN  AA      AA  KK    KK    EE                   |" << endl;
	cout << "|          SSSSSSSSSS  NN     NNN  AA      AA  KK     KK   EEEEEEEEEE           |" << endl;
	cout << "|          SSSSSSSSSS  NN      NN  AA      AA  KK      KK  EEEEEEEEEE           |" << endl;
	cout << "|                                                                               |" << endl;
	cout << "|      Instructions: Try to make the snake as long as possible by eating        |" << endl;
	cout << "|                    the food. '+' = +1 points; 'x' = -3 points.                |" << endl;
	cout << "|                                                                               |" << endl;
	cout << "|      Controls: w = up; s = down; a = left; d = right; p/space = pause         |" << endl;
	cout << "|                                                                               |" << endl;
	cout << "|      Challenge: Get to 100 points and I will treat you to dinner.             |" << endl;
	cout << "|                                                                               |" << endl;
	cout << "|                            PRESS ANY KEY TO START                             |" << endl;
	cout << "|";
	for (int i = 0; i < 39; i++)
		cout << "/ ";
	cout << "/|" << endl;
	while(true) {
		if (kbhit()) {
			command = getchar();
			break;
		}
	}
}

// PlayGame(Game &game)
//		+ Accepts a game
//		- Infinite loop which plays game
//		  until game is over
//		- "wasd" controls snake, 'p' or ' '
//		  pauses the game
void playGame(Game &game) {
	char direction;
	while(true) {
		if (kbhit()) {
			direction = getchar();
			if (direction == 'w')
				game.updateSnake('u');
			else if (direction == 'a')
				game.updateSnake('l');
			else if (direction == 's')
				game.updateSnake('d');
			else if (direction == 'd')
				game.updateSnake('r');
			else if (direction == ' ' || direction == 'p')
				pauseGame(game);
		}
		game.printGame();
		if(!game.updateGame()) {
			break;
		}
		usleep(game.gameSpeed() * 5000);
	}
}

// gameOver()
//		- Outputs game over text
//		- Places game in infinite loop until
//		  'y' or 'n' is pressed to play again or quit
bool gameOver() {
	cout << "Play again? Y/N" << endl;
	
	char option;
	while(true) {
		if (kbhit()) {
			option = getchar();
			if (option == 'y' || option == 'Y') {
				return true;
			}
			else if (option == 'n' || option == 'N') {
				return false;
			}
		}
	}
}

int main() {
	changemode(1);

	Game game = Game(40, 20);

	mainMenu(game);

	while(true) {
		playGame(game);
		game.setHighscore();
		if (!gameOver()) {
			break;
		}
		game.newGame();
	}

	changemode(0);
	return 0;
}

