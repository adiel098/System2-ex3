#include "Player.hpp"
#include "Catan.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>
#include "Board.hpp"

namespace ariel {

    // Default constructor
    Player::Player() : game(nullptr) {
    }

    Player::Player(std::string name, Catan* game) : name(name), points(0), game(game) {
        resources["wood"] = 0;
        resources["brick"] = 0;
        resources["wool"] = 0;
        resources["ore"] = 0;
        resources["wheat"] = 0;
        myturn = 0;
        cardIsUsed=false;
    }

    std::string Player::get_name() const {
        return name;
    }

    int Player::get_points() const {
        return points;
    }

    void Player::add_points(int points) {
        this->points += points;
    }

    void Player::set_id(int id) {
        this->id = id;
    }

    int Player::get_id() {
        return id;
    }

    void Player::set_game(Catan* game) {
        this->game = game;
    }

    std::vector<DevelopmentCard*>& Player::get_player_cards() {
        return game->getBoard().get_developmentCards_by_id(id);
    }

    std::string Player::print() const {
        return name;
    }

    int Player::rollDice() {
        isYourTurn();
        int dice = (std::rand() % 11) + 2;
        std::cout << name<< " roll dice and result = " << dice <<std::endl;

        game->updateResourcesOfPlayers(dice); // Use the game instance

        return dice;
    }

    void Player::endTurn() {
        isYourTurn();

        game->checkKingOfKnights(); // Use the game instance
        game->calculateAndUpdatePoints();

        this->cardIsUsed=false;
        try {
        
        game->checkWinner();
    } catch (const WinnerException& e) {
        std::cout << e.what() << std::endl;
         // Terminate the program gracefully
    }
        game->nextTurn(); // Use the game instance
        std::cout << "--------------- END TURN - " << name << "  ---------------"<<std::endl;
        std::cout << "" << std::endl;


    }
        bool Player::trade(Player p, std::map<std::string, int> give, std::map<std::string, int> get)
        {
        isYourTurn();
        if (canAffordAndBuy(game->getPlayer(p.get_id()).get_resources(), get) && canAffordAndBuy(game->getPlayer(id).get_resources(), give)) 
        {
            reduceResources(give);
            increaseResources(get);
            game->getPlayer(p.get_id()).reduceResources(get);
            game->getPlayer(p.get_id()).increaseResources(give);

            std::cout << "Trade successful between " << this->get_name() << " and " << p.get_name() << std::endl;
            std::cout << this->get_name() << " gave: ";
            for (const auto& item : give) {
                std::cout << item.first << " (" << item.second << "), ";
            }
            std::cout << "and received: ";
            for (const auto& item : get) {
                std::cout << item.first << " (" << item.second << "), ";
            }
            std::cout << std::endl;
            return true;
        } 
        else 
        {
            std::cout << "Trade failed between " << this->get_name() << " and " << p.get_name() << std::endl;
            std::cout << "Insufficient resources for the trade." << std::endl;
            return false;
        }
}

    std::map<std::string, int>& Player::get_resources() {
        return resources;
    }

    void Player::updateResources(const std::string& resource, const int amount) {

        game->getPlayer(id).get_resources()[resource] += amount;
    }

    void Player::reduceResources(std::map<std::string, int>& price) {
        for (const auto& item : price) {
            const std::string& resourceName = item.first;
            int requiredAmount = item.second;
            game->getPlayer(id).get_resources()[resourceName] -= requiredAmount;
        }
    }

    void Player::addResources(std::string res, int amount) {
    game->getPlayer(id).get_resources()[res] += amount;
    std::cout << "Player " << this->get_name() << " received " << amount << " " << res << "(s)." << std::endl;
    std::cout << "" << std::endl;

}


    void Player::removeResources(std::string res, int amount) {
        game->getPlayer(id).get_resources()[res] -= amount;
    }

    void Player::increaseResources(std::map<std::string, int>& price) {
        for (const auto& item : price) {
            const std::string& resourceName = item.first;
            int requiredAmount = item.second;
            game->getPlayer(id).get_resources()[resourceName] += requiredAmount;
        }
    }

    void Player::useKnight() {
        isYourTurn();
        if(!cardIsUsed)
        {
        for (int i = 0; i < game->getPlayer(id).get_player_cards().size(); i++) {
            if ((!game->getPlayer(id).get_player_cards()[i]->isUsed()) && game->getPlayer(id).get_player_cards()[i]->getType() == 0) {
                std::cout << name<<" used Kinght card." <<std::endl;

                game->getPlayer(id).get_player_cards()[i]->useDevelopmentCard();
                this->cardIsUsed=true;
                return;
            }
        }
        
         std::cout << "You dont have unused Kinght card." <<std::endl;
        std::cout << "" <<std::endl;
        }
        else{
            std::cout << "You already used develop card this turn." <<std::endl;
        std::cout << "" <<std::endl;
        }
    }

    void Player::useTwoFreeRoads(Road r1, Road r2) {
        isYourTurn();
        for (int i = 0; i < game->getPlayer(id).get_player_cards().size(); i++) {
            if ((!game->getPlayer(id).get_player_cards()[i]->isUsed()) && game->getPlayer(id).get_player_cards()[i]->getType() == 2) {
                std::cout << name<<" used Two Free Roads card." <<std::endl;

                game->getPlayer(id).get_player_cards()[i]->useDevelopmentCard(*this, r1, r2);
                return;
            }
        }
        std::cout << "You dont have unused Two Free Roads card." <<std::endl;
        std::cout << "" <<std::endl;
    }

    void Player::useYearOfPlenty(std::string res1, std::string res2) {
        isYourTurn();
        for (int i = 0; i < game->getPlayer(id).get_player_cards().size(); i++) {
            if ((!game->getPlayer(id).get_player_cards()[i]->isUsed()) && game->getPlayer(id).get_player_cards()[i]->getType() == 4) {
                    std::cout << name<<" used Year Of Plenty card." <<std::endl;

                game->getPlayer(id).get_player_cards()[i]->useDevelopmentCard(*this, res1, res2);
                return;
            }
        }
        std::cout << "You dont have unused Year Of Plenty card." <<std::endl;
        std::cout << "" <<std::endl;
    }

    void Player::useMonopoly(std::string res) {


        isYourTurn();
        for (int i = 0; i < game->getPlayer(id).get_player_cards().size(); i++) {
            if ((!game->getPlayer(id).get_player_cards()[i]->isUsed()) && game->getPlayer(id).get_player_cards()[i]->getType() == 3) {
                    std::cout << name<<" used Monopoly card." <<std::endl;

                game->getPlayer(id).get_player_cards()[i]->useDevelopmentCard(game->get_players(), *this, res); // Use the game instance
                return;
            }
        }
        std::cout << "You dont have unused Monopoly card." <<std::endl;
        std::cout << "" <<std::endl;

        
    }

    void Player::buyDevelopmentCard() {
        isYourTurn();
        std::map<std::string, int> price;
        price["wool"] = 1;
        price["ore"] = 1;
        price["wheat"] = 1;
        std::map<std::string, int> res = get_resources();
        if (canAffordAndBuy(game->getPlayer(id).get_resources(), price)) {
            reduceResources(price);
            int index = game->getBoard().getDevelopmentCard(id);

            game->getBoard().get_developmentCards()[index]->setPlayerID(id);
            std::cout << "You success bought development card" <<std::endl;
            std::cout << "" <<std::endl;
            return;

        }
        std::cout << "You failed to buy development card" <<std::endl;
        std::cout << "" <<std::endl;

    }

    void Player::placeRoad(int x1, int y1, int x2, int y2) {
        isYourTurn();
        game->getBoard().add_road(get_id(), x1, y1, x2, y2); // Use the game instance
    }

    void Player::buySettlement(int x, int y) {
        isYourTurn();
        std::map<std::string, int> price;
        price["wool"] = 1;
        price["wood"] = 1;
        price["wheat"] = 1;
        price["brick"] = 1;
        std::map<std::string, int> res = get_resources();
        if (canAffordAndBuy(game->getPlayer(id).get_resources(), price)) {
            reduceResources(price);

            game->getBoard().add_building(get_id(), 1, x, y); // Use the game instance
        }
         else{
            std::cout << "You dont have enough resources to buy settlement " <<std::endl;
            std::cout << "" <<std::endl;

        }
    }

    void Player::placeSettlement(int x, int y) {
        
        isYourTurn();

        game->getBoard().add_building(get_id(), 0, x, y); // Use the game instance
        game->updateResPlayerFirstTurn(id);
        
    }

    void Player::buyTown(int x, int y) {
        isYourTurn();
        std::map<std::string, int> price;
        price["ore"] = 3;
        price["wheat"] = 2;
        if (canAffordAndBuy(game->getPlayer(id).get_resources(), price)) {

            bool flag =game->getBoard().upgrade_building(id, 2, x, y); // Use the game instance
            int i=0;;
             // Use the game instance
             if(flag)
             {
            for (const auto& building : game->getBoard().get_buildings()) {
                
                        if (building.getPlayerID() == id) {
                            if(building.getX()==x&&building.getY()==y)
                                game->getBoard().get_buildings().at(i).setType();
                                reduceResources(price);
  
                                return;
                                }
                                i++;
                                
            }
             }
        }
        else{
            std::cout << "Upgrade settlement failed " <<std::endl;
            std::cout << "" <<std::endl;

        }
    }

    void Player::buyRoad(int x1, int y1, int x2, int y2) {
        isYourTurn();
        std::map<std::string, int> price;
        price["wood"] = 1;
        price["brick"] = 1;
        std::map<std::string, int> res = get_resources();

        if (canAffordAndBuy(game->getPlayer(id).get_resources(), price)) {
            reduceResources(price);
            game->getBoard().add_road(get_id(), x1, y1, x2, y2); // Use the game instance
        }
    }

    void Player::printPoints() {
        isYourTurn();
        std::cout << get_name() << " has " << get_points() << " points" << std::endl;
    }

    bool Player::canAffordAndBuy(std::map<std::string, int>& resources, std::map<std::string, int>& price) {
        // Check if resources are sufficient for the purchase
        for (const auto& item : price) {
            const std::string& resourceName = item.first;
            int requiredAmount = item.second;

            // If the resource is not found or the amount is insufficient, return false
            if (resources.find(resourceName) == resources.end() || resources[resourceName] < requiredAmount) {
                return false;
            }
        }

        return true;
    }

    void Player::isYourTurn() {
        if (game->getTurn() != get_id()) { // Use the game instance
            throw std::invalid_argument("this is not your turn\n");
        }
    }
   void Player::printResources() const {
    std::cout << "Resources of player " << name << ": ";
    bool first = true;
    for (const auto& resource : game->getPlayer(id).get_resources()) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << resource.first << ": " << resource.second;
        first = false;
    }
    std::cout << std::endl;
    std::cout << std::endl;

}
        void Player::set_points(int number)
        {
            this->points=number;
        }

}
