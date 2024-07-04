//id: 207988213 email:haleviadiel@gmail.com
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
    this->y=y;
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
    return type;
    
}