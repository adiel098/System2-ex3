#include "catan.hpp"
#include "board.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include "player.hpp"


namespace ariel{

        // Default constructor
        Catan::Catan() 
        {}

        
        Catan::Catan(Player& p1,Player& p2,Player& p3)
        {
            this->players[0] =p1;
            this->players[1] =p2;
            this->players[2] =p3;
            this->turn=0;
            this->b =  Board();
        
        }


    
    
        void Catan::ChooseStartingPlayer() 
        {
            // p1.print();
            // p1.startTurn();
        }
        Board Catan::getBoard() 
        {
            return b;
        }
        std::vector<Player> Catan::get_players() 
        {
            return players;
        }
        void Catan::updateResourcesOfPlayers(int diceNumber) //after any roll
        {
            for (const auto& tile : getBoard().get_tiles()) 
            {
            if (tile.get_data() == diceNumber) //check if this tile number == dice number
            {

                for (const auto& set : getBoard().get_settlements()) //runnig on all the settlements
                {

                    for (const auto& pair : tile.get_cornersXY()) //runnig on all the tile corners
                    {
                        if (pair.first == set.get_x() && pair.second == set.get_y()) //if settlement on this tile
                        {
                            
                            get_players()[set.get_playerID()].updateResources(tile.get_resource(),set.get_type());// update the resources of the player
                            
                        }
                    }
                }
                
            }
            }
            }
    };
           

