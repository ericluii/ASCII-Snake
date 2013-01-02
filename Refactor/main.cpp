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
#include "onePlayerGame.h"
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

int main() {
	changemode(1);

	onePlayerGame game = onePlayerGame(40, 20, 5);

	game.mainMenu();

	while(true) {
		game.playGame();
		game.setHighscore();
		if (!game.gameOver()) {
			break;
		}
		game.newGame();
	}

	changemode(0);
	return 0;
}

