#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include "Tile.hpp"
#include "Road.hpp"
#include "Building.hpp"
#include "DevelopmentCard.hpp"

namespace ariel {
        class Catan; // Forward declaration if needed
        class Building; // Forward declaration if needed

    class Board {
    private:
        std::vector<Tile> tiles;
        std::vector<Road> roads;
        std::vector<Building> buildings;
        std::vector<DevelopmentCard*> developmentCards;

    public:
        Board();
        std::vector<Tile>& get_tiles();
        std::vector<Road>& get_roads();
        std::vector<Building>& get_buildings();
        std::vector<DevelopmentCard*>& get_developmentCards();
        int getDevelopmentCard(int id);
        std::vector<Building> get_buildings_by_id(int playerID);
        std::vector<Road> get_roads_by_id(int playerID);
        void initializeBoard(std::vector<Tile>& tiles, std::vector<Building>& buildings, std::vector<Road>& roads, std::vector<DevelopmentCard*>& developmentCards);
        bool isXYInBoard(int x, int y);
        void add_road(int playerID, int x1, int y1, int x2, int y2);
        bool upgrade_building(int playerID, int type, int x, int y);
        void add_building(int playerID, int type, int x, int y);
        bool validRoad(int playerID, int x1, int y1, int x2, int y2);
        bool validBuilding(int playerID, int type, int x, int y);
        DevelopmentCard* getDevelopmentCardpointer(int id);
        std::vector<DevelopmentCard*>& get_developmentCards_by_id(int id) ;

    };
}

#endif // BOARD_HPP
