#ifndef _game_h
#define _game_h

#include <vector>
#include "food.h"

class Game {
    protected:
        int width;
        int height;
        std::vector< std::vector<char> > board;
        std::vector<Food> prey;
        virtual void addFood() = 0;
    public:
        Game(int width, int height);
        void mainMenu() const;
        virtual void newGame() = 0;
        virtual void playGame() = 0;
        void pauseGame() const;
        bool gameOver() const;
        virtual bool updateGame() = 0;
        virtual int* snakeSpeed() = 0;
};

#endif
