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

            this->turn=-1;
            this->winner=-1;
            this->b = Board();

        }


    
    
        void Catan::ChooseStartingPlayer() 
        {
            std::cout<< this->players[0].get_name() << " is starting the game" <<std::endl;
            this->turn=this->players[0].get_id();

        }
        void Catan::setTurn(int turn)
        {
            turn=turn;
        }
        int Catan::getTurn()
        {
            return turn;
        }

        void Catan::nextTurn() 
        {
            if(getTurn()+1==(get_players().size()))
            {
                turn=get_players()[0].get_id();
            }
            else{
                setTurn(getTurn()+1);
            }

        }
        void Catan::printWinner() 
        {
            if(checkWinner())
            {
                std::cout<< "the winner is" << winner<<std::endl;
            }
            else{
                std::cout<< "no one reach 10 points so no winner" << std::endl;
            }
        }
        Board Catan::getBoard() 
        {
            return b;
        }
        void Catan::checkKingOfKnights()
        {
            int maxKnights = 0;
            int kingPlayerID = -1; // Initialize to an invalid ID

            for (int i = 0; i < get_players().size(); i++)
            {
                int knights = 0;

                for (int j = 0; j < get_players()[i].get_developmentCards().size(); j++)
                {
                    if (get_players()[i].get_developmentCards()[j].getType() == 0    // Assuming type 0 represents knight cards
                        && get_players()[i].get_developmentCards()[j].isUsed())
                    {
                        knights++;
                    }
                }

                if (knights >= 3 && knights > maxKnights)
                {
                    maxKnights = knights;
                    kingPlayerID = get_players()[i].get_id();
                }
            }

            // Update the kingOfKnights and kingPlayerID if a player has more used knight cards
            if (maxKnights > kingOfKnightsCount)
            {
                kingOfKnightsCount = maxKnights;
                kingOfKnightsID = kingPlayerID;
            }
        }
     
        std::vector<Player>& Catan::get_players() 
        {
            return players;
        }
        bool Catan::checkWinner() 
        {
            for(int i=0;i<get_players().size();i++)
            {
                int points=get_players()[i].get_points();
                if(kingOfKnightsID==get_players()[i].get_id())
                {
                    points+=2;
                }

                if(points>=10)
            
                {
                    std::cout<< get_players()[i].get_name() << " is the winner" <<std::endl;
                    winner=get_players()[i].get_id();
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
           

