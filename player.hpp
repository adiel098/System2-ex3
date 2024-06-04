#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <map>
#include "board.hpp"
#include <vector>

namespace ariel
{



    class Player 
        {

        private:
            
            std::string name;
            int points;
            int myturn;
            std::map<std::string, int> resources;
            std::vector<DevelopmentCard> developmentCards;


        public:
            Player(std::string name);
            Player();

            //fields
 
            //functions
            
        
            std::string Player::get_name() const;
             std::map<std::string, int> Player::get_resources() ;

            int Player::get_points() const;

            std::string Player::print() const;
            int Player::rollDice() const;
            void Player::endTurn() ;
            void Player::startTurn() ;
            void Player::buyDevelopmentCard() ;
            void Player::buyTown() ;
            void Player::buySettlement() ;
            void Player::buyRoad() ;
            void Player::placeRoad() ;

            void Player::printPoints() ;
            bool canAffordAndBuy(std::map<std::string, int>& resources,  std::map<std::string, int>& price);
            void Player::updateResources(const std::string& resource ,const int amount);
            void Player::reduceResources(std::map<std::string, int>& price);








        };
};

#endif