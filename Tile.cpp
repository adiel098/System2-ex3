//id: 207988213 email:haleviadiel@gmail.com

#include <string>
#include <vector>
#include <memory>
#include "Tile.hpp"


using namespace ariel;

   
    
        Tile::~Tile(){};
        Tile::Tile( std::string tileType ,std::string resource ,std::vector<std::pair<int, int>>&  cornersXY ,int data)
        {
                this-> type= tileType;
                this->resource = resource;
                this->cornersXY = cornersXY;
                this->data = data;
        }
       
         std::vector<std::pair<int, int>> Tile::get_cornersXY() const
        {
            return cornersXY;
            
        }
        std::string Tile::get_resource() const
        {
            return resource;
        
        }
        int Tile::get_data() const
        {
            return data;
        
        }
    
    
   

    
         
    


