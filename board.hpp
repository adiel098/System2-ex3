#ifndef BOARD_HPP
#define BOARD_HPP
#include "board.hpp"
#include "Tile.hpp"
#include "Road.hpp"

#include "DevelopmentCard.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <random>
#include "../../../../../usr/include/c++/11/bits/algorithmfwd.h"
#include "Building.hpp"
#include "Building.hpp" 
namespace ariel
{

    class DevelopmentCard;  // Forward declaration
    class Road;  // Forward declaration
    class Building;  // Forward declaration

    class Board 
        {

        private:
            static std::vector<Tile*>tiles;
            static std::vector<Building> buildings;
            static std::vector<Road> roads;
            static std::vector<DevelopmentCard> developmentCards;
        public:
            Board();
            Board(std::string name);
            void initializeBoard(std::vector<Tile*>& tiles,std::vector<Building>& buildings, std::vector<Road>& roads,std::vector<DevelopmentCard>& developmentCards) ;
            static bool isXYInBoard(int x, int y);
          
            static std::vector<DevelopmentCard>& get_developmentCards() ;
            static std::vector<Building>& get_buildings() ;
            static std::vector<Road>& get_roads() ;
            static std::vector<Tile*>& get_tiles() ;
            static std::vector<Building>& get_buildings_by_id(int playerID) ;
            static std::vector<Road>& get_roads_by_id(int playerID) ;
            static void add_road(int playerID,int x1,int y1, int x2 , int y2);
            static void add_building(int playerID,int type,int x,int y);
            static void upgrade_building(int playerID,int type,int x,int y);

            static DevelopmentCard& getDevelopmentCard(int id);
            static bool validRoad(int playerID,int x1,int y1,int x2,int y2);
            static bool validBuilding(int playerID,int type,int x,int y);


            //fields
            
 
            //functions
            



        
        };
}
#endif