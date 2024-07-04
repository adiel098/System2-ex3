// id: 207988213 email: haleviadiel@gmail.com
#include "Catan.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include <sstream>

namespace ariel {

    // Default constructor
    Catan::Catan() : turn(-1), winner(-1), kingOfKnightsCount(0), kingOfKnightsID(-1), b(new Board()) {}

    // Constructor with players
    Catan::Catan(Player& p1, Player& p2, Player& p3) 
        : turn(-1), winner(-1), kingOfKnightsCount(0), kingOfKnightsID(-1), b(new Board()) {
        
        p1.set_id(0);
        p1.set_game(this);
        this->players.push_back(p1);

        p2.set_id(1);
        p2.set_game(this);
        this->players.push_back(p2);

        p3.set_id(2);
        p3.set_game(this);
        this->players.push_back(p3);

    }

    void Catan::ChooseStartingPlayer() {
        std::cout << this->players[0].get_name() << " is starting the game" << std::endl;
        std::cout <<"" << std::endl;

        this->turn = this->players[0].get_id();
    }

    void Catan::setTurn(int turn) {
        this->turn = turn;
    }

    int Catan::getTurn() const {
        return turn;
    }

    void Catan::nextTurn() {
        if (getTurn() + 1 == players.size()) {
            turn = players[0].get_id();
        } else {
            setTurn(getTurn() + 1);
        }
    }

    void Catan::printWinner() {
        if (checkWinner()) {
            std::cout << "The winner is player with ID: " << winner << std::endl;
        } else {
            std::cout << "No one has reached 10 points, so there is no winner" << std::endl;
        }
    }

    Board& Catan::getBoard() {
        return *b;
    }

    void Catan::checkKingOfKnights() {
        int maxKnights = 0;
        int kingPlayerID = -1; // Initialize to an invalid ID

        for (int i = 0; i < players.size(); i++) {
            int knights = 0;

            for (int j = 0; j < players[i].get_player_cards().size(); j++) {
                if (players[i].get_player_cards()[j]->getType() == 0 && players[i].get_player_cards()[j]->isUsed()) {
                    knights++;
                }
            }

            if (knights >= 3 && knights > maxKnights) {
                maxKnights = knights;
                kingPlayerID = players[i].get_id();
            }
        }

        // Update the kingOfKnights and kingPlayerID if a player has more used knight cards
        if (maxKnights > kingOfKnightsCount) {
            kingOfKnightsCount = maxKnights;
            kingOfKnightsID = kingPlayerID;
        }
    }

   

    bool Catan::checkWinner() {
    std::stringstream str;
    for (int i = 0; i < get_players().size(); i++) {
        int points = get_players()[i].get_points();

        if (points >= 10) {
            str << get_players()[i].get_name() << " is the winner" << std::endl;
            throw WinnerException(str.str());

            // winner = get_players()[i].get_id(); // This line is unreachable, so it can be removed
            // return true; // This line is unreachable, so it can be removed
        }
    }
    return false;
}

    void Catan::updateResourcesOfPlayers(int diceNumber) {
        for (auto& tile : b->get_tiles()) {
            if (tile.get_data() == diceNumber) { // Check if this tile number == dice number
                for (const auto& set : b->get_buildings()) { // Running on all the settlements
                    for (const auto& pair : tile.get_cornersXY()) { // Running on all the tile corners
                        if (pair.first == set.getX() && pair.second == set.getY()) { // If settlement on this tile
                            players[set.getPlayerID()].updateResources(tile.get_resource(), set.getType()); // Update the resources of the player
                            std::cout << "dice = "<<diceNumber<< " and " <<players[set.getPlayerID()].get_name( ) << " got " <<set.getType()<< " "<< tile.get_resource()<< std::endl;

                        }
                    }
                }
            }
        }
    }
    void Catan::updateResPlayerFirstTurn(int id) {
        if(b->get_buildings_by_id(id).size()==1)
            
                for (const auto& set : b->get_buildings_by_id(id)) {
                    for (auto& tile : b->get_tiles()) {
                        if (tile.get_data() != 0)
                        {  //if not desert
                        for (const auto& pair : tile.get_cornersXY()) { 
                            // Running on all the tile corners
                            if (pair.first == set.getX() && pair.second == set.getY()) 
                            { // If settlement on this tile
                                players[id].updateResources(tile.get_resource(), set.getType()); // Update the resources of the player

                            }
                        }
                        }
                }
                }
            
        
    }

    void Catan::setPlayer(int index, Player& player) {
        if (index >= 0 && index < players.size()) {
            players[index] = player;
        }
    }

    Player& Catan::getPlayer(int index) {
        if (index >= 0 && index < players.size()) {
            return players[index];
        }
        throw std::out_of_range("Player index out of range");
    }
     std::vector<Player>& Catan::get_players() {
        return players;
    }
    void Catan::printAllBuildings() const {
    const auto& buildings = b->get_buildings();
    if (buildings.empty()) {
        std::cout << "No buildings on the board." << std::endl;
        return;
    }

    std::cout << "Buildings on the board:" << std::endl;
        std::cout << "" << std::endl;

    for (const auto& building : buildings) {
        std::cout << "Player ID: " << building.getPlayerID()
                  << ", Type: " << building.getType()
                  << ", Location: (" << building.getX() << ", " << building.getY() << ")" << std::endl;
    }
    std::cout << "" << std::endl;
}
void Catan::printAllPlayerPoints() const {
    std::cout << "Points of all players:" << std::endl;
        std::cout << "" << std::endl;

    for (const auto& player : players) {
        std::cout << "Player " << player.get_name() << ": " << player.get_points() << " points" << std::endl;
    }
    std::cout << "" << std::endl;

    if(kingOfKnightsID!=-1)
    {
     std::cout << "Player " << players[kingOfKnightsID].get_name() << ": " << "got 2 points cause Bigest Army" << std::endl;;

    }
}
void Catan::calculateAndUpdatePoints() {
    // Reset points for all players
    for (auto& player : players) {
        player.set_points(0);
    }

    // Calculate points based on buildings
    const auto& buildings = b->get_buildings();
    for (const auto& building : buildings) {
        int playerID = building.getPlayerID();
        int type = building.getType();
        if (type == 1) {
            players[playerID].add_points(1);
        } else if (type == 2) {
            players[playerID].add_points(2);
        }
    }
    if(kingOfKnightsID!=-1)
    {
        
    players[kingOfKnightsID].add_points(2);

    }
    for (auto& player : players) {
        const auto& devCards = player.get_player_cards();
        for (const auto& card : devCards) {
            if (card->getType() == 1 ) {
                player.add_points(1);
            }
        }
    }
}
}
