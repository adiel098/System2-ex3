//id: 207988213 email:haleviadiel@gmail.com
#include "Player.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>
#include "board.hpp"



namespace ariel{

        // Default constructor
        Player::Player() 
        {}


        Player::Player(std::string name)
        {
            this->name =name;
            this->points=0;
            this->resources["wood"] = 0;
            this->resources["brick"] = 0;
            this->resources["wool"] = 0;
            this->resources["Ore"] = 0;
            this->resources["wheat"] = 0;
            
            myturn=0;


        
        }


    std::string Player::get_name() const
    {
        return name;
    }
    int Player::get_points() const
    {
        return points;
    }
    void Player::add_points(int points)
    {
        this->points+=points;
    }

    void Player::set_id(int id) 
    {
        this->id=id;
    }
    

    int Player::get_id() 
    {
        return id;
    }
    std::vector<DevelopmentCard>& Player::get_developmentCards()
    {
        return developmentCards;
    }

    std::string Player::print() const
    {
        return name;
    }
    int Player::rollDice() const
    {   
        isYourTurn();
        int dice = (std::rand() % 11) + 2;
        Catan::updateResourcesOfPlayers(dice);

        return dice;
    }
    void Player::endTurn() 
    {
        isYourTurn();
        Catan::checkKingOfKnights();
        Catan::checkWinner();
        Catan::nextTurn();
    }
    void Player::trade(Player p,std::map<std::string, int> give , std::map<std::string, int> get) 
    {
       isYourTurn();
        if(canAffordAndBuy(p.get_resources(),get)&&canAffordAndBuy(get_resources(),give))
        {
            reduceResources(give);
            increaseResources(get);
            p.reduceResources(get);
            p.increaseResources(give);
            std::cout<< "trade success" << std::endl;

        }
        else{
            std::cout<< "trade failed" << std::endl;

        }

    }
    std::map<std::string, int> &Player::get_resources() 
    {
        return resources;
    }

    void Player::updateResources(const std::string& resource,const int amount)

    {
        resources[resource]+=amount; 
           }
    void Player::reduceResources(std::map<std::string, int>& price)

    {
        for (const auto& item : price) 
        {
            const std::string& resourceName = item.first;
            int requiredAmount = item.second;
            resources[resourceName] -= requiredAmount;
        }
    }
    void Player::addResources(std::string res, int amount)
    {
        this->get_resources()[res]+=amount;
    }
    void Player::removeResources(std::string res, int amount)
    {
        this->get_resources()[res]-=amount;
    }

    void Player::increaseResources(std::map<std::string, int>& price)

    {
        for (const auto& item : price) 
        {
            const std::string& resourceName = item.first;
            int requiredAmount = item.second;
            resources[resourceName] += requiredAmount;
        }
    }
    void Player::useKnight()
    {
        isYourTurn();
        for(int i =0;i<get_developmentCards().size();i++)
        {
            if((!get_developmentCards()[i].isUsed())&&get_developmentCards()[i].getType()==0)
            {
                get_developmentCards()[i].useDevelopmentCard();
            }
        }
    }
    void Player::useTwoFreeRoads(Road r1, Road r2)
    {
        isYourTurn();
        for(int i =0;i<get_developmentCards().size();i++)
        {
            if((!get_developmentCards()[i].isUsed())&&get_developmentCards()[i].getType()==0)
            {
                get_developmentCards()[i].useDevelopmentCard(*this,r1,r2);
            }
        }
    }
     void Player::useYearOfPlenty(std::string res1, std::string res2)
    {
        isYourTurn();
        for(int i =0;i<get_developmentCards().size();i++)
        {
            if((!get_developmentCards()[i].isUsed())&&get_developmentCards()[i].getType()==0)
            {
                get_developmentCards()[i].useDevelopmentCard(*this,res1,res2);
            }
        }
    }
      void Player::useMonopoly( std::string res)
    {
        isYourTurn();
        for(int i =0;i<get_developmentCards().size();i++)
        {
            if((!get_developmentCards()[i].isUsed())&&get_developmentCards()[i].getType()==0)
            {
                get_developmentCards()[i].useDevelopmentCard(Catan::get_players(),*this,res);
            }
        }
    }

    
    void Player::buyDevelopmentCard() 
    {
        isYourTurn();
        std::map<std::string, int> price;
        price["wool"] = 1;
        price["ore"] = 1;
        price["wheat"] = 1;
        std::map<std::string, int> res=get_resources();
        if(canAffordAndBuy(res,price))
        {
            reduceResources(price);
            DevelopmentCard d=Board::getDevelopmentCard(get_id());
            if(d.getType()==1)//check if victory point
            {
                d.setUsedTrue();
                this->add_points(1);
            }
            developmentCards.push_back(d);
        }
    }
     void Player::placeRoad(int x1,int y1, int x2, int y2) 
    {
       isYourTurn();
            Board::add_road(get_id(),x1,y1,x2,y2);
    }
        
    
    void Player::buySettlement(int x,int y) 
    {
        isYourTurn();
        std::map<std::string, int> price;
        price["wool"] = 1;
        price["wood"] = 1;
        price["wheat"] = 1;
        price["brick"] = 1;
        std::map<std::string, int> res=get_resources();
        if(canAffordAndBuy(res,price))
        {
            reduceResources(price);
            Board::add_building(get_id(),1,x,y);
        }
    }
    
    void Player::placeSettlement(int x,int y) 
    {
        isYourTurn();
        Board::add_building(get_id(),1,x,y);
    }
    void Player::buyTown(int x,int y) 
    {
        isYourTurn();
        std::map<std::string, int> price;
        price["ore"] = 3;
        price["wheat"] = 2;
        std::map<std::string, int> res=get_resources();
        if(canAffordAndBuy(res,price))
        {
            reduceResources(price);
            Board::upgrade_building(get_id(),2,x,y);
        }    
    }
      void Player::buyRoad(int x1,int y1, int x2, int y2) 
    {
        isYourTurn();
         std::map<std::string, int> price;
        price["wood"] = 1;
        price["brick"] = 1;
        std::map<std::string, int> res=get_resources();

        if(canAffordAndBuy(res,price))
        {
            reduceResources(price);
            Board::add_road(get_id(),x1,y1,x2,y2);

        }
    }
    void Player::printPoints() 
    {
        isYourTurn();
        std::cout<< get_name() << "has" << get_points()<<std::endl;
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

    // Deduct the resources for the purchase

    return true;
}
  void Player::isYourTurn() 
        {

        if(Catan::getTurn()!=get_id())
                {
                    throw std::invalid_argument("this is not your turn\n");
                }
            
        }


};