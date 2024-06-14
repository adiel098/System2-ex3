//id: 207988213 email:haleviadiel@gmail.com
#ifndef ROAD_HPP
#define ROAD_HPP
#include <string>
#include "board.hpp"


namespace ariel
{


   

    class Road {
    
    private:
        int playerID;
        int x1,y1,x2,y2;


    public:
        Road();
        Road(int playerID,int x1,int y1, int x2, int y2);
        int get_playerID() const;
        int get_x1() const;
        int get_x2() const;
        int get_y1() const;
        int get_y2() const;
        bool operator==(Road& other)const;



    };
}
#endif