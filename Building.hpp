//id: 207988213 email:haleviadiel@gmail.com
#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "Player.hpp"

#define SETTLEMENT 1
#define CITY 2


namespace ariel {
    class Building {
    private:
        int playerID;
        int x,y,type;

    public:
        Building(int playerID,int type,int x,int y);
        ~Building();
        int getType() const;
        int getX() const;
        int getY() const;
        int getPlayerID() const;
        void setType();


    };
}

#endif 