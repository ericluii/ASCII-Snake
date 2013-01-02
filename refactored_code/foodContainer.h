#ifndef _foodContainer_h
#define _foodContainer_h

#include <vector>
#include "food.h"

class FoodContainer : private std::vector<Food*> {
    public:
        FoodContainer(){}
        int amountOfFood() const;
        bool addFood(Food* aFood);
        void removeFood(Food* aFood);
        void removeAllFood();
        Food* getFood(int index);
        bool containsHelpfulFood() const;
};

#endif
