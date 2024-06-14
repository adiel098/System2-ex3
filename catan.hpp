//id: 207988213 email:haleviadiel@gmail.com
#include "board.hpp"
#include "Player.hpp"

#ifndef CATAN_HPP
#define CATAN_HPP


namespace ariel
{

       class Player;  // Forward declaration
    class Board;  // Forward declaration


    class Catan 
        {

        private:
            //constructors
            static Board b;
            static int turn;
            static int winner;
            static int kingOfKnightsCount,kingOfKnightsID;
            static std::vector<Player> players;
        public:
            Catan(Player& p1,Player& p2,Player& p3);
            Catan();

            //fields
            
            //functions
            std::string get_name() const;
            void ChooseStartingPlayer() ;
             void printWinner() ;
            //void checkLongestRoad();
            static void checkKingOfKnights();
            //int calculateRoads(Player p);
             static Board getBoard(); 
            static int getTurn(); 
            static void setTurn(int turn); 
            static std::vector<Player>& get_players()  ;
            static void updateResourcesOfPlayers(int diceNumber);
             static bool checkWinner() ;
            static void nextTurn() ;




        };
};

#endif