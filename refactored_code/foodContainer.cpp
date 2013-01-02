#include "foodContainer.h"
#include <cstdlib>
#include <time.h>

int FoodContainer::amountOfFood() const {
    return this->size();
}

bool FoodContainer::addFood(Food* aFood) {
    for(int i = 0; i < amountOfFood(); i++) {
        if ((*this)[i]->position() == aFood->position()) {
            return false;
        }
    }
    
    this->push_back(aFood);
    
    return true;
}

void FoodContainer::removeFood(Food* aFood) {
    for(int i = 0; i < amountOfFood(); i++) {
        if ((*this)[i]->position() == aFood->position()) {
            delete (*this)[i];
            this->erase(this->begin() + i);
            break;
        }
    }
}

void FoodContainer::removeAllFood() {
    int total = amountOfFood();
    
    for(int i = 0; i < total; i++) {
        delete(*this)[0];
        this->erase(this->begin());
        break;
    }
}

Food* FoodContainer::getFood(int index) {
    return (*this)[index];
}

bool FoodContainer::containsHelpfulFood() const {

	for (int i = 0; i < amountOfFood(); i++) {
		if ((*this)[i]->getType() % 2 == 0) {
			return true;
		}
	}
    
	return false;
}