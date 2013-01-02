#include "game.h"
#include <vector>
#include <iostream>

using namespace std;

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

Game::Game(int width, int height):
    width(width), height(height), board(width, vector<char>(height)), prey() {
    
    // Sets board values(empty board)
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            board[i][j] = ' ';
        }
    }
}

void Game::mainMenu() const {
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

void Game::pauseGame() const {
    cout << "\t\tGAME PAUSED - P/SPACE TO RESUME - Q TO QUIT" << endl;
	char command;
    
	while(true) {
		if (kbhit()) {
			command = getchar();
			if (command == ' ' || command == 'p') {
				break;
			}
			else if (command = 'q') {
				exit(0);
			}
		}
	}
}

bool Game::gameOver() const {
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