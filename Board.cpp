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
#include "Building.hpp"
#include "Building.hpp" 


namespace ariel{

        
            
        Board::Board() 
        {

            
            initializeBoard(tiles,buildings,roads,developmentCards);
          

        }
          std::vector<Tile*>& Board::get_tiles() 
        {
            return tiles;
    
        }
         std::vector<Road>& Board::get_roads() 
        {
            return roads;
    
        }
        std::vector<Building>& Board:: get_buildings() 
        {
            return buildings;
    
        }
         std::vector<DevelopmentCard>& Board::get_developmentCards() 
        {
            return developmentCards;
    
        }
        DevelopmentCard& Board::getDevelopmentCard(int id)
        {
            for (size_t i=0;i<25;i++)
            {
                if(!(get_developmentCards()[i].isUsed()&&get_developmentCards()[i].getPlayerID()==-1))
                {
                    DevelopmentCard d=get_developmentCards()[i];
                    d.setPlayerID(id);
                    return d;
                }
            }
                throw std::runtime_error("No unused DevelopmentCard found in the vector");
        }

       
        
        
        std::vector<Building>& Board::get_buildings_by_id(int playerID) 
        {
            std::vector<Building> playerSettlements;
            size_t i=0;
            for (const auto& set : get_buildings()) {
            if (set.getPlayerID() == playerID) {
                playerSettlements[i]=(set);
                i++;
            }
            return playerSettlements;
    
        }
        }
        std::vector<Road>& Board::get_roads_by_id(int playerID) 
        {
            std::vector<Road> playerRoads;
            size_t i=0;
            for (const auto& set : get_roads()) {
            if (set.get_playerID() == playerID) {
                playerRoads[i]=(set);
                i++;
            }
            return playerRoads;
    
        }
        }
        void Board::initializeBoard(std::vector<Tile*>&tiles,std::vector<Building>& buildings, std::vector<Road>& roads, std::vector<DevelopmentCard>& developmentCards) 
        {
            // Add Knight cards
            for (size_t i = 0; i < 14; ++i) {
                developmentCards[i]=DevelopmentCard(0);  
            }

            // Add Victory Point cards
            for (size_t i = 14; i < 19; ++i) {
                developmentCards[i]=DevelopmentCard(1);     
                       }

            // Add Progress cards
            
            developmentCards[19]=(DevelopmentCard(2));
            developmentCards[20]=DevelopmentCard(2);
            developmentCards[21]=DevelopmentCard(3);
            developmentCards[21]=DevelopmentCard(3);
            developmentCards[23]=DevelopmentCard(4);
            developmentCards[24]=DevelopmentCard(4);
            

            std::vector<std::vector<std::string>> resourceTypes = {
            {"Mountains","ore"},
            {"Mountains","ore"},
            {"Mountains","ore"},
            {"Pasture Land","wool"},
            {"Pasture Land","wool"},
            {"Pasture Land","wool"},
            {"Pasture Land","wool"},
            {"Agricultural Land","wheat"},
            {"Agricultural Land","wheat"},
            {"Agricultural Land","wheat"},
            {"Agricultural Land","wheat"},
            {"Forest","wood"},
            {"Forest","wood"},
            {"Forest","wood"},
            {"Hills","brick"},
            {"Hills","brick"},
            {"Hills","brick"},
            {"Desert","desert"},

            };

        std::vector<int> numberTokens = {
            2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12
        };
        std::vector<std::vector<std::pair<int, int>>> cornersXY = {
            
        {{4,1}, {5,0}, {5,2}, {6,0}, {6,2}, {7,1}},
        {{4,3}, {5,2}, {5,4}, {6,2}, {6,4}, {7,3}},
        {{4,5}, {5,4}, {5,6}, {6,4}, {6,6}, {7,5}},
        {{4,7}, {5,6}, {5,8}, {6,6}, {6,8}, {7,7}},
        {{4,9}, {5,8}, {5,10}, {6,8}, {6,10}, {7,9}},

        {{0,3}, {1,2}, {1,4}, {2,2}, {2,4}, {3,3}},
        {{0,5}, {1,4}, {1,6}, {2,4}, {2,6}, {3,5}},
        {{0,7}, {1,6}, {1,8}, {2,6}, {2,8}, {3,7}},
        {{8,3}, {1,2}, {1,4}, {2,2}, {2,4}, {11,3}},
        {{8,5}, {1,4}, {1,6}, {2,4}, {2,6}, {11,5}},
        {{8,7}, {1,6}, {1,8}, {2,6}, {2,8}, {11,7}},
        
        {{3,1}, {4,1}, {3,3}, {4,3}, {2,2}, {5,2}},
        {{3,3}, {4,3}, {3,5}, {4,5}, {2,4}, {5,4}},
        {{3,5}, {4,5}, {3,7}, {4,7}, {2,6}, {5,6}},
        {{3,7}, {4,7}, {3,9}, {4,9}, {2,8}, {5,8}},

        {{7,1}, {8,1}, {7,3}, {8,3}, {6,2}, {9,2}},
        {{7,3}, {8,3}, {7,5}, {8,5}, {6,4}, {9,4}},
        {{7,5}, {8,5}, {7,7}, {8,7}, {6,6}, {9,6}},
        {{7,7}, {8,7}, {7,9}, {8,9}, {6,8}, {9,8}}};
        // Shuffle resource types and number tokens
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(resourceTypes.begin(), resourceTypes.end(), gen);
        std::shuffle(numberTokens.begin(), numberTokens.end(), gen);
        std:shuffle(developmentCards.begin(),developmentCards.end(),gen);
        std::shuffle(cornersXY.begin(), cornersXY.end(), gen);
        // Fill the tiles vector with resource types and number tokens
        size_t index = 0;
        for (size_t i = 0; i < tiles.size(); ++i) {
                if (resourceTypes[index][0] != "Desert") {
                    tiles[i]=(TileFactory::createTile(resourceTypes[index][0],resourceTypes[index][1],cornersXY[i],numberTokens[index]));

                    ++index;
                } else {
                    // If it's a desert tile, set the number token to 0
                    tiles[i]=(TileFactory::createTile("Desert","desert",cornersXY[index], 0));
                }
            
        }
    
         
        }
        bool Board::isXYInBoard(int x, int y)
        {
            std::vector<std::pair<int, int>> outBoardsPairs = {
        {6, 1}, {6, 3}, {5, 1}, {5, 3}, {5, 5}, {5, 7}, {5, 9}, {6, 5}, {6, 7}, {6, 9},
        {7, 0}, {0, 9}, {0, 1}, {8, 9}, {8, 1}, {8, 7}, {1, 7}, {1, 9}, {2, 9}, {2, 1},
        {2, 7}, {11, 0}, {11, 9}, {11, 1}};
        std::vector<std::pair<int, int>> allPairs = {
        {4, 1}, {5, 0}, {5, 2}, {6, 0}, {6, 2}, {7, 1},
        {4, 3}, {5, 2}, {5, 4}, {6, 2}, {6, 4}, {7, 3},
        {4, 5}, {5, 4}, {5, 6}, {6, 4}, {6, 6}, {7, 5},
        {4, 7}, {5, 6}, {5, 8}, {6, 6}, {6, 8}, {7, 7},
        {4, 9}, {5, 8}, {5, 10}, {6, 8}, {6, 10}, {7, 9},
        {0, 3}, {1, 2}, {1, 4}, {2, 2}, {2, 4}, {3, 3},
        {0, 5}, {1, 4}, {1, 6}, {2, 4}, {2, 6}, {3, 5},
        {0, 7}, {1, 6}, {1, 8}, {2, 6}, {2, 8}, {3, 7},
        {8, 3}, {1, 2}, {1, 4}, {2, 2}, {2, 4}, {11, 3},
        {8, 5}, {1, 4}, {1, 6}, {2, 4}, {2, 6}, {11, 5},
        {8, 7}, {1, 6}, {1, 8}, {2, 6}, {2, 8}, {11, 7},
        {3, 1}, {4, 1}, {3, 3}, {4, 3}, {2, 2}, {5, 2},
        {3, 3}, {4, 3}, {3, 5}, {4, 5}, {2, 4}, {5, 4},
        {3, 5}, {4, 5}, {3, 7}, {4, 7}, {2, 6}, {5, 6},
        {3, 7}, {4, 7}, {3, 9}, {4, 9}, {2, 8}, {5, 8},
        {7, 1}, {8, 1}, {7, 3}, {8, 3}, {6, 2}, {9, 2},
        {7, 3}, {8, 3}, {7, 5}, {8, 5}, {6, 4}, {9, 4},
        {7, 5}, {8, 5}, {7, 7}, {8, 7}, {6, 6}, {9, 6},
        {7, 7}, {8, 7}, {7, 9}, {8, 9}, {6, 8}, {9, 8}
    };
        std::pair<int, int> targetPair = {x, y};
        for (const auto& pair : allPairs) {
            if (pair == targetPair) {
                return true;
            }
        }
        return false;
        }
        void Board::add_road(int playerID,int x1,int y1, int x2 , int y2)
        {
           
                    if(validRoad( playerID, x1,y1, x2,y2))
                    {
                     Road r=Road(playerID,x1,y1,x2,y2);
                     get_roads().push_back(r);
                    }
                
            

        }
        
        void Board::upgrade_building(int playerID,int type,int x,int y)
        {
            for(int i=0;i<get_buildings_by_id(playerID).size();i++)
            {
                if(get_buildings_by_id(playerID)[i].getX()==x&&get_buildings_by_id(playerID)[i].getY()&&get_buildings_by_id(playerID)[i].getType()==1)
                {
                    get_buildings_by_id(playerID)[i].setType();
                }

            }
        }

        void Board::add_building(int playerID,int type,int x,int y)
        {
            
                    if(validBuilding( playerID,type, x,y))
                    {
                     
                        Building b= Building(playerID,type, x,y);
                     
                        get_buildings().push_back(b);
                    }
                
            

        }
        bool Board::validRoad(int playerID,int x1,int y1,int x2,int y2)
            {
                if(isXYInBoard(x1,y1)&&isXYInBoard(x2,y2))//if the road on the board
                {
                    Road r=Road(playerID, x1,y1, x2, y2);
                    for (const auto& road : get_roads()) {//if already road in same location
                            if (road == r) 
                            {return false;}
                    }
                    for (const auto& set :get_buildings() ) {
                            if (set.getX ()== x1&&set.getX ()== y1&&set.getPlayerID()!=playerID) //if the road continues a settlemnet of other player
                            {return false;}
                    }
                    for (const auto& road : get_roads_by_id(playerID)) {
                            if (road.get_x2() ==x1&&road.get_y2()==y1) //if the road not continues other road
                            {return true;}
                    }
                    for (const auto& set :get_buildings_by_id(playerID) ) {
                            if (set.getX ()== x1&&set.getY()== y1) //if the road continues a settlemnet 
                            {return true;}
                    }
                }
                return false;

            }
        bool Board::validBuilding(int playerID,int type,int x,int y)
            {
                if(isXYInBoard(x,y))//if the road on the board
                {
                    bool flag=false;
                    Road r;
                    for (const auto& set : get_buildings()) {//if setlement already exist on same location
                            if (set.getX() == x&&set.getY() == y )
                            {return false;}
                    }
                    if(type==0)//if its simple setlement
                    {
                        if(get_buildings_by_id(playerID).size()<2)//check if its start of game
                        {
                            if(isXYInBoard(x-1,y+1)) // check if there another build closer less than 1 road
                            {
                                for (const auto& b : get_buildings())
                                {
                                    if(b.getX()==x-1&&b.getY()==y+1)
                                    {
                                        return false;
                                    }
                                }
                            }
                            if(isXYInBoard(x+1,y+1))
                            {
                                for (const auto& b : get_buildings())
                                {
                                    if(b.getX()==x+1&&b.getY()==y+1)
                                    {
                                        return false;
                                    }
                                }
                            }
                            if(isXYInBoard(x-1,y-1))
                            {
                                for (const auto& b : get_buildings())
                                {
                                    if(b.getX()==x-1&&b.getY()==y-1)
                                    {
                                        return false;
                                    }
                                }
                            }
                            if(isXYInBoard(x+1,y-1))
                            {
                                for (const auto& b : get_buildings())
                                {
                                    if(b.getX()==x+1&&b.getY()==y-1)
                                    {
                                        return false;
                                    }
                                }
                            }
                            if(isXYInBoard(x,y-1))
                            {
                                for (const auto& b : get_buildings())
                                {
                                    if(b.getX()==x&&b.getY()==y-1)
                                    {
                                        return false;
                                    }
                                }
                            }
                            if(isXYInBoard(x,y+1))
                            {
                                for (const auto& b : get_buildings())
                                {
                                    if(b.getX()==x&&b.getY()==y+1)
                                    {
                                        return false;
                                    }
                                }
                            }
                            if(isXYInBoard(x-1,y))
                            {
                                for (const auto& b : get_buildings())
                                {
                                    if(b.getX()==x-1&&b.getY()==y)
                                    {
                                        return false;
                                    }
                                }
                            }
                            if(isXYInBoard(x+1,y))
                            {
                                for (const auto& b : get_buildings())
                                {
                                    if(b.getX()==x+1&&b.getY()==y)
                                    {
                                        return false;
                                    }
                                }
                            }
                            return true;
                                
                        }
                        if(get_buildings_by_id(playerID).size()>=5)///check if player have already 5 setlements ( this the limit)
                        {
                            return false;
                        }
                    }
                    for (const auto& road : get_roads_by_id(playerID)) {
                            if (road.get_x2() == x&&road.get_y2() == y )
                            {
                                flag= true;
                                r=road;
                            }
                    }
                    if(flag)
                    {
                        for (const auto& road : get_roads_by_id(playerID)) //check if there is a two roads 1 by 1 to the settlement
                        {
                            if (road.get_x2() == r.get_x1()&&road.get_y2() == r.get_y1() )
                            {return true;}
                         }

                    }
                }
                return false;
                    
        } 
        


 
};