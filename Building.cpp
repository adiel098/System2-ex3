#include "Building.hpp"
#include <iostream>

using namespace ariel;

#define SETTLEMENT 1
#define CITY 2


ariel::Building::Building(int playerID, int type, int x, int y)
{
    this->type = type;
    this->playerID = playerID;
    this->x=x;
    this->x=x;
}

Building::~Building() {}

int Building::getX() const {
    return x;
}
void Building::setType()  {
    this->type=2;
}
int Building::getPlayerID() const {
    return playerID;
}

int Building::getY() const {
    return y;
}

int Building::getType() const {
    switch (this->type) {
        case SETTLEMENT:
            return 1;
        case CITY:
            return 2;
       
        default:
            return 0;
    }
}