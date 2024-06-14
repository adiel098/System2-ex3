#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <map>
#include "board.hpp"
#include "DevelopmentCard.hpp"

#include <vector>
#include <string>

namespace ariel
{


    class DevelopmentCard;  // Forward declaration
    class Player 
        {

        private:
            
            std::string name;
            int points;
            int myturn;
            int id;
            std::map<std::string, int> resources;
            std::vector<DevelopmentCard>  developmentCards;


        public:
            Player(std::string name);
            Player();

            //fields
 
            //functions
            
        
            std::string get_name() const;
            std::map<std::string, int>& get_resources() ;
            std::vector<DevelopmentCard>& get_developmentCards();
            int get_points() const;
            void add_points(int points);
            int get_id() const;
            void set_id(int id) ;

            std::string print() const;
            int rollDice() const;
            void trade(Player p,std::map<std::string, int> give , std::map<std::string, int> get) ;

            void endTurn() ;
            void startTurn() ;
            void buyDevelopmentCard() ;
            void buyTown(int x,int y) ;
            void buySettlement(int x,int y) ;
            void placeSettlement(int x,int y) ;

            void buyRoad(int x1,int y1, int x2, int y2) ;
            void placeRoad(int x1,int y1, int x2, int y2) ;

            void printPoints() ;
            bool canAffordAndBuy(std::map<std::string, int>& resources,  std::map<std::string, int>& price);
            void updateResources(const std::string& resource ,const int amount);
            void reduceResources(std::map<std::string, int>& res);
            void increaseResources(std::map<std::string , int>& res);
            void addResources(std::string res, int amount);
            void removeResources(std::string res, int amount);
            













        };
};

#endif