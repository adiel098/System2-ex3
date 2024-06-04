#include "board.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <random>
#include "../../../../../usr/include/c++/11/bits/algorithmfwd.h"


namespace ariel{


        
        Settlement::Settlement() 
            {}

            Settlement::Settlement(int type, int playerID,int x,int y)
            {
                this->type =type;
                this->playerID=playerID;
                this->x=x;
                this->y=y;
            }
            bool Settlement::validSettlement(Board b,int playerID,int type,int x,int y)
            {
                if(Board::isXYInBoard(x,y))//check if location is on board
                {
                    bool flag=false;
                    Road r;
                    for (const auto& set : b.get_settlements()) {//if setlement already exist on same location
                            if (set.get_x() == x&&set.get_y() == y )
                            {return false;}
                    }
                    if(type==0)//if its simple setlement
                    {
                        if(b.get_settlements_by_id(playerID).size()>=5)///check if player have already 5 setlements ( this the limit)
                        {
                            return false;
                        }
                    }
                    for (const auto& road : b.get_roads_by_id(playerID)) {
                            if (road.get_x2() == x&&road.get_y2() == y )
                            {
                                flag= true;
                                r=road;
                            }
                    }
                    if(flag)
                    {
                        for (const auto& road : b.get_roads_by_id(playerID)) //check if there is a two roads 1 by 1 to the settlement
                        {
                            if (road.get_x2() == r.get_x1()&&road.get_y2() == r.get_y1() )
                            {return true;}
                         }

                    }
                }
                return false;
                    
        }



        Tile::Tile() 
            {}

            Tile::Tile(std::string type,std::string resource,std::vector<std::pair<int, int>> cornersXY, int data)
            {
                this->type =type;
                this->resource=resource;
                this->cornersXY=cornersXY;
                this->data =data;
            }
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
            void Road::setRoad(Board b,int playerID,int x1,int y1,int x2,int y2) 
            {
                if(Board::isXYInBoard(x1,y1)&&Board::isXYInBoard(x2,y2))
                {

                }
            }
            bool Road::validRoad(Board b,int playerID,int x1,int y1,int x2,int y2)
            {
                if(Board::isXYInBoard(x1,y1)&&Board::isXYInBoard(x2,y2))//if the road on the board
                {
                Road r=Road(playerID, x1,y1, x2, y2);
                for (const auto& road : b.get_roads()) {//if already road in same location
                        if (road == r) 
                        {return false;}
                }
                for (const auto& set :b.get_settlements() ) {
                        if (set.get_x ()== x1&&set.get_y ()== y1&&set.get_playerID()!=playerID) //if the road continues a settlemnet of other player
                        {return false;}
                }
                for (const auto& road : b.get_roads_by_id(playerID)) {
                        if (road.get_x2() ==x1&&road.get_y2()==y1) //if the road not continues other road
                        {return true;}
                }
                 for (const auto& set :b.get_settlements_by_id(playerID) ) {
                        if (set.get_x ()== x1&&set.get_y ()== y1) //if the road continues a settlemnet 
                        {return true;}
                }
                }
                return false;

            }
            bool Road::operator==(Road& other)const
            {
                return(this->get_x1()==other.get_x1()&&this->get_x2()==other.get_x2()&&this->get_y1()==other.get_y1()&&this->get_y2()==other.get_y2());
            }

            
        DevelopmentCard::DevelopmentCard() 
            {}

            DevelopmentCard::DevelopmentCard(std::string type)
            {
                this->type =type;
                this->used=false;

            }
            
        Board::Board() 
        {

            int size;
            std::vector<Tile> tiles;

            std::vector<Settlement> settlements;
            std::vector<Road> roads;
            std::vector<DevelopmentCard> developmentCards=std::vector<DevelopmentCard> (25);
            initializeBoard(tiles,settlements,roads,developmentCards);


        }
          std::vector<Tile> Board::get_tiles() const
        {
            return tiles;
    
        }
        std::vector<Road> Board::get_roads() const
        {
            return roads;
    
        }
        std::vector<Settlement> Board::get_settlements() const
        {
            return settlements;
    
        }
         std::vector<DevelopmentCard> Board::get_developmentCards() const
        {
            return developmentCards;
    
        }

       
        std::string Tile::get_resource() const
        {
            return resource;
    
        }
        std::vector<std::pair<int, int>> Tile::get_cornersXY() const
        {
            return cornersXY;
    
        }
        int Settlement::get_type() const
        {
            return type;
    
        }
        int Settlement::get_playerID() const
        {
            return playerID;
    
        }
        int Settlement::get_x() const
        {
            return x;
    
        }
        int Settlement::get_y() const
        {
            return y;
    
        }
        std::vector<Settlement> Board::get_settlements_by_id(int playerID) const
        {
            std::vector<Settlement> playerSettlements;
            int i=0;
            for (const auto& set : get_settlements()) {
            if (set.get_playerID() == playerID) {
                playerSettlements[i]=(set);
                i++;
            }
            return playerSettlements;
    
        }
        }
        std::vector<Road> Board::get_roads_by_id(int playerID) const
        {
            std::vector<Road> playerRoads;
            int i=0;
            for (const auto& set : get_roads()) {
            if (set.get_playerID() == playerID) {
                playerRoads[i]=(set);
                i++;
            }
            return playerRoads;
    
        }
        }
        void Board::initializeBoard(std::vector<Tile>&tiles,std::vector<Settlement>& settlements, std::vector<Road>& roads,std::vector<DevelopmentCard>& developmentCards) 
        {
            // Add Knight cards
            developmentCards.resize(14);
            for (int i = 0; i < 14; ++i) {
                developmentCards[i]=(DevelopmentCard("Knight"));
            }

            // Add Victory Point cards
            for (int i = 14; i < 19; ++i) {
                developmentCards[i]=(DevelopmentCard("VictoryPoint"));     
                       }

            // Add Progress cards
            
            developmentCards[19]=(DevelopmentCard("2Ways"));
            developmentCards[20]=(DevelopmentCard("2Ways"));
            developmentCards[21]=(DevelopmentCard("Monopol"));
            developmentCards[22]=(DevelopmentCard("Monopol"));
            developmentCards[23]=(DevelopmentCard("2Cards"));
            developmentCards[24]=(DevelopmentCard("2Cards"));
            

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
                    tiles[i] = Tile(resourceTypes[index][0],resourceTypes[index][1],cornersXY[index] ,numberTokens[index]);
                    ++index;
                } else {
                    // If it's a desert tile, set the number token to 0
                    tiles[i] = Tile("Desert","desert",cornersXY[index], 0);
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
        

 
};