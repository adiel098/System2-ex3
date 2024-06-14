#include "catan.hpp"
#include "board.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "Player.hpp"


namespace ariel{

        // Default constructor
        Catan::Catan() 
        {}

        
        Catan::Catan(Player& p1,Player& p2,Player& p3)
        {
            this->players[0] =p1;
            this->players[0].set_id(0);
            this->players[1] =p2;
            this->players[1].set_id(1);

            this->players[2] =p3;
            this->players[2].set_id(2);

            this->turn=0;
            this->b =  Board();

        }


    
    
        void Catan::ChooseStartingPlayer() 
        {
            std::cout<< this->players[0].get_name() << " is starting the game" <<std::endl;
        }
        void Catan::printWinner() 
        {
            // p1.print();
            // p1.startTurn();
        }
        Board Catan::getBoard() 
        {
            return b;
        }
        void Catan::checkKingOfKnights()
        {
            int maxKnights = 0;
            int kingPlayerID = -1; // Initialize to an invalid ID

            for (int i = 0; i < this->players.size(); i++)
            {
                int knights = 0;

                for (int j = 0; j < this->players[i].get_developmentCards().size(); j++)
                {
                    if (this->players[i].get_developmentCards()[j].getType() == 0    // Assuming type 0 represents knight cards
                        && this->players[i].get_developmentCards()[j].isUsed())
                    {
                        knights++;
                    }
                }

                if (knights >= 3 && knights > maxKnights)
                {
                    maxKnights = knights;
                    kingPlayerID = this->players[i].get_id();
                }
            }

            // Update the kingOfKnights and kingPlayerID if a player has more used knight cards
            if (maxKnights > this->kingOfKnightsCount)
            {
                this->kingOfKnightsCount = maxKnights;
                this->kingOfKnightsID = kingPlayerID;
            }
}
     
        std::vector<Player> Catan::get_players() 
        {
            return players;
        }
        bool Catan::checkWinner() 
        {
            for(int i=0;i<this->players.size();i++)
            {
                if(this->players[0].get_points()>=10)
            
                {
                    std::cout<< this->players[0].get_name() << " is the winner" <<std::endl;
                    return true;
                }
            }
        }
        void Catan::updateResourcesOfPlayers(int diceNumber) //after any roll
        {
            for ( auto& tile : getBoard().get_tiles()) 
            {
            if (tile->get_data() == diceNumber) //check if this tile number == dice number
            {

                for (const auto& set : getBoard().get_buildings()) //runnig on all the settlements
                {

                    for (const auto& pair : tile->get_cornersXY()) //runnig on all the tile corners
                    {
                        if (pair.first == set.getX() && pair.second == set.getY()) //if settlement on this tile
                        {
                            
                            get_players()[set.getPlayerID()].updateResources(tile->get_resource(),set.getType());// update the resources of the player
                            
                        }
                    }
                }
                
            }
            }
            }
    };
           

