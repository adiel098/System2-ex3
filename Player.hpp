#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <map>
#include "Board.hpp"
#include "DevelopmentCard.hpp"
#include "Road.hpp"
#include "Building.hpp"

namespace ariel {
    class Catan; // Forward declaration of Catan class

    class Player {
    private:
        std::string name;
        int points;
        std::map<std::string, int> resources;
        //std::vector<DevelopmentCard*>& developmentCards;
        int id;
        int myturn;
        bool cardIsUsed;
        Catan* game; // Pointer to Catan instance

    public:
        Player();
        Player(std::string name, Catan* game); // Update constructor

        std::string get_name() const;
        int get_points() const;
        void add_points(int points);
        void set_id(int id);
        int get_id();
        void set_game(Catan* game); // New method to set the game pointer
        std::vector<DevelopmentCard*>& get_player_cards();
        std::string print() const;
        int rollDice();
        void endTurn();
        void trade(Player p, std::map<std::string, int> give, std::map<std::string, int> get);
        std::map<std::string, int>& get_resources();
        void updateResources(const std::string& resource, const int amount);
        void reduceResources(std::map<std::string, int>& price);
        void addResources(std::string res, int amount);
        void removeResources(std::string res, int amount);
        void increaseResources(std::map<std::string, int>& price);
        void useKnight();
        void useTwoFreeRoads(Road r1, Road r2);
        void useYearOfPlenty(std::string res1, std::string res2);
        void useMonopoly(std::string res);
        void buyDevelopmentCard();
        void placeRoad(int x1, int y1, int x2, int y2);
        void buySettlement(int x, int y);
        void placeSettlement(int x, int y);
        void buyTown(int x, int y);
        void buyRoad(int x1, int y1, int x2, int y2);
        void printPoints();
        bool canAffordAndBuy(std::map<std::string, int>& resources, std::map<std::string, int>& price);
        void isYourTurn();
        void printResources() const;
        void set_points(int number);
    };
}

#endif // PLAYER_HPP
