// id: 207988213 email: haleviadiel@gmail.com
#include "Board.hpp"
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
#include <algorithm>
#include "Player.hpp"
#include <iomanip> 

namespace ariel {

    Board::Board() {
        initializeBoard(tiles, buildings, roads, developmentCards);
    }

    std::vector<Tile>& Board::get_tiles() {
        return tiles;
    }

    std::vector<Road>& Board::get_roads() {
        return roads;
    }

    std::vector<Building>& Board::get_buildings() {
        return buildings;
    }

    std::vector<DevelopmentCard*>& Board::get_developmentCards() {
        return developmentCards;
    }
     std::vector<DevelopmentCard*>& Board::get_developmentCards_by_id(int id) {
    static std::vector<DevelopmentCard*> empty_cards; // Use a static vector to return a reference
    std::vector<DevelopmentCard*>* cards = new std::vector<DevelopmentCard*>;

    for (auto& card : developmentCards) {

        if (card->getPlayerID() == id) {
            cards->push_back(card);
        }
    }

    if (cards->empty()) {
        delete cards; // Clean up if no matching cards were found
        return empty_cards;
    } else {
        return *cards;
    }
}
    
    DevelopmentCard* Board::getDevelopmentCardpointer(int id) {
        int index=0;
        for (auto& card : developmentCards) {
            //std::cout <<card->getType()<< "card " <<card->getPlayerID()<<std::endl;

            if (card->getPlayerID() == -1) {
                
                card->setPlayerID(id);
                developmentCards[index]->setPlayerID(id);
                std::cout <<card->getType()<< " bought  " <<card->getPlayerID()<<std::endl;

                return card;
            }
        }

        std::cout <<"no avaliable cards"<<std::endl;

    }
    

   int Board::getDevelopmentCard(int id) {
    int index = 0;
    for (auto& card : developmentCards) {
        // Print the current state before making changes

        if (card->getPlayerID() == -1) {

            // Set the player ID
            card->setPlayerID(id);
            developmentCards[index]->setPlayerID(id); // This might be a test value, ensure it's as intended

            // Print the state after setting the player ID


            return index;
        }
        index++;
    }
    throw std::runtime_error("No unused DevelopmentCard found in the vector");
}

    std::vector<Building> Board::get_buildings_by_id(int playerID) {
        std::vector<Building> playerBuildings;
        for (const auto& building : buildings) {
            if (building.getPlayerID() == playerID) {
                playerBuildings.push_back(building);
            }
        }
        return playerBuildings;
    }

    std::vector<Road> Board::get_roads_by_id(int playerID) {
        std::vector<Road> playerRoads;
        for (const auto& road : roads) {
            if (road.get_playerID() == playerID) {
                playerRoads.push_back(road);
            }
        }
        return playerRoads;
    }

    void Board::initializeBoard(std::vector<Tile>& tiles, std::vector<Building>& buildings, std::vector<Road>& roads, std::vector<DevelopmentCard*>& developmentCards) {
        try {

            // Clear and reserve space for vectors
            tiles.clear();
            buildings.clear();
            roads.clear();
            developmentCards.clear();

            tiles.reserve(19); // Expected number of tiles for a Catan board
            buildings.reserve(50); // Arbitrary large number
            roads.reserve(50); // Arbitrary large number
            developmentCards.reserve(25); // 14 knights + 5 VP + 6 progress

            // Add Knight cards
            for (size_t i = 0; i < 3; ++i) {
                developmentCards.push_back(new DevelopmentCard(0));
            }
                developmentCards.push_back(new DevelopmentCard(1));
                developmentCards.push_back(new DevelopmentCard(2));
                developmentCards.push_back(new DevelopmentCard(3));
                developmentCards.push_back(new DevelopmentCard(4));

            // Add Victory Point cards
            for (size_t i = 14; i < 19; ++i) {
                developmentCards.push_back(new DevelopmentCard(1));
            }

            // Add Progress cards
            developmentCards.push_back(new DevelopmentCard(2));
            developmentCards.push_back(new DevelopmentCard(2));
            developmentCards.push_back(new  DevelopmentCard(3));
            developmentCards.push_back( new DevelopmentCard(3));
            developmentCards.push_back(new DevelopmentCard(4));
            developmentCards.push_back(new DevelopmentCard(4));

            std::vector<std::pair<std::string, std::string>> resourceTypes = {
                {"Mountains", "ore"}, {"Mountains", "ore"}, {"Mountains", "ore"},
                {"Pasture Land", "wool"}, {"Pasture Land", "wool"}, {"Pasture Land", "wool"}, {"Pasture Land", "wool"},
                {"Agricultural Land", "wheat"}, {"Agricultural Land", "wheat"}, {"Agricultural Land", "wheat"}, {"Agricultural Land", "wheat"},
                {"Forest", "wood"}, {"Forest", "wood"}, {"Forest", "wood"},
                {"Hills", "brick"}, {"Hills", "brick"}, {"Hills", "brick"},
                {"Desert", "desert"}
            };

            std::vector<int> numberTokens = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};

            std::vector<std::vector<std::pair<int, int>>> cornersXY = {
                {{4, 1}, {5, 0}, {5, 2}, {6, 0}, {6, 2}, {7, 1}},
                {{4, 3}, {5, 2}, {5, 4}, {6, 2}, {6, 4}, {7, 3}},
                {{4, 5}, {5, 4}, {5, 6}, {6, 4}, {6, 6}, {7, 5}},
                {{4, 7}, {5, 6}, {5, 8}, {6, 6}, {6, 8}, {7, 7}},
                {{4, 9}, {5, 8}, {5, 10}, {6, 8}, {6, 10}, {7, 9}},
                {{0, 3}, {1, 2}, {1, 4}, {2, 2}, {2, 4}, {3, 3}},
                {{0, 5}, {1, 4}, {1, 6}, {2, 4}, {2, 6}, {3, 5}},
                {{0, 7}, {1, 6}, {1, 8}, {2, 6}, {2, 8}, {3, 7}},
                {{8, 3}, {1, 2}, {1, 4}, {2, 2}, {2, 4}, {11, 3}},
                {{8, 5}, {1, 4}, {1, 6}, {2, 4}, {2, 6}, {11, 5}},
                {{8, 7}, {1, 6}, {1, 8}, {2, 6}, {2, 8}, {11, 7}},
                {{3, 1}, {4, 1}, {3, 3}, {4, 3}, {2, 2}, {5, 2}},
                {{3, 3}, {4, 3}, {3, 5}, {4, 5}, {2, 4}, {5, 4}},
                {{3, 5}, {4, 5}, {3, 7}, {4, 7}, {2, 6}, {5, 6}},
                {{3, 7}, {4, 7}, {3, 9}, {4, 9}, {2, 8}, {5, 8}},
                {{7, 1}, {8, 1}, {7, 3}, {8, 3}, {6, 2}, {9, 2}},
                {{7, 3}, {8, 3}, {7, 5}, {8, 5}, {6, 4}, {9, 4}},
                {{7, 5}, {8, 5}, {7, 7}, {8, 7}, {6, 6}, {9, 6}},
                {{7, 7}, {8, 7}, {7, 9}, {8, 9}, {6, 8}, {9, 8}}
            };

            //Shuffle resource types and number tokens
            // std::random_device rd;
            // std::mt19937 gen(rd());
            // std::shuffle(resourceTypes.begin(), resourceTypes.end(), gen);
            // std::shuffle(numberTokens.begin(), numberTokens.end(), gen);
            // std::shuffle(developmentCards.begin(), developmentCards.end(), gen);
            // std::shuffle(cornersXY.begin(), cornersXY.end(), gen);

            size_t index = 0;
            for (size_t i = 0; i < resourceTypes.size(); ++i) {
                if (resourceTypes[i].first != "Desert") {
                    tiles.push_back(Tile(resourceTypes[i].first, resourceTypes[i].second, cornersXY[i], numberTokens[index]));
                    index++;
                } else {
                    tiles.push_back(Tile("Desert", "desert", cornersXY[i], 0));
                    

                }
            }

        } catch (const std::exception& e) {
            std::cerr << "Exception in initializeBoard: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception in initializeBoard" << std::endl;
        }
    }

    bool Board::isXYInBoard(int x, int y) {
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
        return std::find(allPairs.begin(), allPairs.end(), targetPair) != allPairs.end();
    }

    void Board::add_road(int playerID, int x1, int y1, int x2, int y2) {
        if (validRoad(playerID, x1, y1, x2, y2)) {

            Road r = Road(playerID, x1, y1, x2, y2);
            roads.push_back(r);
        }
    }

    bool Board::upgrade_building(int playerID, int type, int x, int y) {
        for (auto& building : get_buildings_by_id(playerID)) {
           

            if (building.getPlayerID() == playerID && building.getX() == x && building.getY() == y && building.getType() == 1) {
                
                building.setType();
                get_buildings_by_id(playerID).push_back(building);
                return true;
            }
           
        }
       
        std::cout << "You dont have any settlement in that location to upgrade to town" << std::endl;
        std::cout << "" << std::endl;
        return false;
          
    }

    void Board::add_building(int playerID, int type, int x, int y) {

        if (validBuilding(playerID, type, x, y)) {

            if(type==0)
            {
                Building a = Building(playerID, 1, x, y);
                buildings.push_back(a);

            }
            else{
                Building b = Building(playerID, type, x, y);
                buildings.push_back(b);

            }
        }
    }

    bool Board::validRoad(int playerID, int x1, int y1, int x2, int y2) {
    if (isXYInBoard(x1, y1) && isXYInBoard(x2, y2)) {
        Road r = Road(playerID, x1, y1, x2, y2);
        for (const auto& road : roads) {
            if (road == r) {
                std::cout << "Place road failed for player ID " << playerID
                          << " from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << "): Road already exists." << std::endl << std::endl;
                return false;
            }
        }
        for (const auto& building : buildings) {
            if ((building.getX() == x1 && building.getY() == y1 && building.getPlayerID() != playerID) ||
                (building.getX() == x2 && building.getY() == y2 && building.getPlayerID() != playerID)) {
                std::cout << "Place road failed for player ID " << playerID
                          << " from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << "): Connected to another player's building." << std::endl << std::endl;
                return false;
            }
        }
        for (const auto& road : get_roads_by_id(playerID)) {
            if ((road.get_x2() == x1 && road.get_y2() == y1) || (road.get_x2() == x2 && road.get_y2() == y2)) {
                std::cout << "Place road successful for player ID " << playerID
                          << " from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")." << std::endl << std::endl;
                return true;
            }
        }

        for (const auto& building : get_buildings_by_id(playerID)) {
            if ((building.getX() == x1 && building.getY() == y1) || (building.getX() == x2 && building.getY() == y2)) {
                std::cout << "Place road successful for player ID " << playerID
                          << " from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")." << std::endl << std::endl;
                return true;
            }
        }
    }
    std::cout << "Place road failed for player ID " << playerID
              << " from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << "): Invalid position or no connected road." << std::endl << std::endl;
    return false;
}


    bool Board::validBuilding(int playerID, int type, int x, int y) {

    if (isXYInBoard(x, y)) {
        for (const auto& building : buildings) {
            if (building.getX() == x && building.getY() == y) {
                std::cout << "Place Settlement failed for player ID " << playerID
                          << " at (" << x << ", " << y << "): Already exists on the same location." << std::endl << std::endl;
                return false;
            }
        }

        if (type == 0) {
            if (get_buildings_by_id(playerID).size() < 2) {
                std::vector<std::pair<int, int>> adjacentPositions = {
                    {x-1, y+1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x, y-1}, {x, y+1}, {x-1, y}, {x+1, y}
                };
                for (const auto& pos : adjacentPositions) {
                    if (isXYInBoard(pos.first, pos.second)) {
                        for (const auto& b : buildings) {
                            if (b.getX() == pos.first && b.getY() == pos.second) {
                                std::cout << "Place Settlement failed for player ID " << playerID
                                          << " at (" << x << ", " << y << "): Adjacent settlement exists." << std::endl << std::endl;
                                return false;
                            }
                        }
                    }
                }
                std::cout << "Place Settlement successful for player ID " << playerID
                          << " at (" << x << ", " << y << ")." << std::endl << std::endl;
                return true;
            }
            if (get_buildings_by_id(playerID).size() >= 5) {
                std::cout << "Place Settlement failed for player ID " << playerID
                          << " at (" << x << ", " << y << "): Too many settlements." << std::endl << std::endl;
                return false;
            }
        }

        bool flag = false;
        Road r;

        for (const auto& road : get_roads_by_id(playerID)) {
            if ((road.get_x2() == x && road.get_y2() == y) || (road.get_x1() == x && road.get_y1() == y)) {
                flag = true;
                r = road;
            }
        }
        if (flag) {
            for (const auto& road : get_roads_by_id(playerID)) {
                if ((road.get_x2() == r.get_x1() && road.get_y2() == r.get_y1()) ||
                    (road.get_x1() == r.get_x2() && road.get_y1() == r.get_y2())) {
                    std::cout << "Place Settlement successful for player ID " << playerID
                              << " at (" << x << ", " << y << ")." << std::endl << std::endl;
                    return true;
                }
            }
        }
    }

    std::cout << "Place Settlement failed for player ID " << playerID
              << " at (" << x << ", " << y << "): Invalid position or no connected road." << std::endl << std::endl;
    return false;
}







}
