#include "board.hpp"
#include "Player.hpp"

#ifndef CATAN_HPP
#define CATAN_HPP


namespace ariel
{

   

    class Catan 
        {

        private:
            //constructors
            Board b;
            int turn;
            int kingOfKnightsCount,kingOfKnightsID;
            std::vector<Player> players;
        public:
            Catan(Player& p1,Player& p2,Player& p3);
            Catan();

            //fields
            
            //functions
            std::string get_name() const;
            void ChooseStartingPlayer() ;
             void printWinner() ;
            void checkLongestRoad();
            void checkKingOfKnights();
            int calculateRoads(Player p);
             Board getBoard(); 
             std::vector<Player> get_players()  ;
            void updateResourcesOfPlayers(int diceNumber);
             bool checkWinner() ;




        };
};

#endif