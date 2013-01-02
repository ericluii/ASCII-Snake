#ifndef _onePlayerGame_h
#define _onePlayerGame_h

#include "game.h"
#include "snake.h"
#include "food.h"

class onePlayerGame : public Game {
    private:
        int score;
        int highscore;
        Snake snake;
        void addFood();
        bool updateGame();
        void printGame() const;
    public:
        onePlayerGame(int width, int height, int snakeLength);
        void newGame();
        void playGame();
        bool setHighscore();
        int* snakeSpeed();
};

#endif