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
    

    int Player::get_id() const
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
        return (std::rand() % 11) + 2;
    }
    void Player::endTurn() 
    {
        myturn=0;
    }
    void Player::trade(Player p,std::map<std::string, int> give , std::map<std::string, int> get) 
    {
       
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
        
    }

    {
        for(int i =0;i<get_developmentCards().size();i++)
        {
            if(get_developmentCards()[i].get)
        }
    }
    void Player::buyDevelopmentCard() 
    {
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
       
            Board::add_road(get_id(),x1,y1,x2,y2);
    }
        
    
    void Player::buySettlement(int x,int y) 
    {
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
        Board::add_building(get_id(),1,x,y);
    }
    void Player::buyTown(int x,int y) 
    {
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

    }
    bool canAffordAndBuy(std::map<std::string, int>& resources, std::map<std::string, int>& price) {
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
  


};