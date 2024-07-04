//id: 207988213 email:haleviadiel@gmail.com
#include "Road.hpp"
#include "Board.hpp"
#include <string>
#include <vector>
#include <memory>


namespace ariel{
    
    Road::Road() 
            {}

            Road::Road(int playerID,int x1,int y1, int x2, int y2)
            {
                this->playerID=playerID;
                this->x1=x1;
                this->y1=y1;
                this->x2=x2;
                this->y2=y2;

            } 
            int Road::get_x1() const
            {
                return x1;
            } 
            int Road::get_x2() const
            {
                return x2;
            } 
            int Road::get_y1() const
            {
                return y1;
            } 
            int Road::get_y2() const
            {
                return y2;
            } 
            int Road::get_playerID() const
            {
                return playerID;
            }

      
            bool Road::operator==(Road& other)const
            {
                return(this->get_x1()==other.get_x1()&&this->get_x2()==other.get_x2()&&this->get_y1()==other.get_y1()&&this->get_y2()==other.get_y2());
            }

}
