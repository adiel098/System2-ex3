#include "board.hpp"
#include "player.hpp"

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
            std::vector<Player> players;
        public:
            Catan(Player& p1,Player& p2,Player& p3);
            Catan();

            //fields
            
            //functions
            std::string get_name() const;
            void ChooseStartingPlayer() ;
             Board getBoard(); 
             std::vector<Player> get_players()  ;
            void updateResourcesOfPlayers(int diceNumber);




        };
};

#endif