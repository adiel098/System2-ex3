#include "player.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>



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
    std::map<std::string, int>Player::get_resources() 
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
        }
    }
     void Player::placeRoad() 
    {
        
    }
    void Player::buySettlement() 
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
        }
    }
    void Player::buyTown() 
    {
        std::map<std::string, int> price;
        price["ore"] = 3;
        price["wheat"] = 2;
        std::map<std::string, int> res=get_resources();
        if(canAffordAndBuy(res,price))
        {
            reduceResources(price);
        }    
    }
      void Player::buyRoad() 
    {
        std::map<std::string, int> price;
        price["wood"] = 1;
        price["brick"] = 1;
        std::map<std::string, int> res=get_resources();
        if(canAffordAndBuy(res,price))
        {
            reduceResources(price);
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