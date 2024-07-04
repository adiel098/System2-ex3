//id: 207988213 email:haleviadiel@gmail.com
#include "DevelopmentCard.hpp"

#include <iostream>
#include "Catan.hpp"
#include "Player.hpp"

using namespace ariel;

DevelopmentCard::DevelopmentCard(int type) {
    this->type = type;
    this->used = false;
    this->playerID=-1;
}

DevelopmentCard::~DevelopmentCard() {}

int DevelopmentCard::getType() const {

    return type;
}
int DevelopmentCard::getPlayerID() const {

    return playerID;
}
void DevelopmentCard::setPlayerID(int id)  {

    this-> playerID=id;
}

bool DevelopmentCard::isUsed() const {

    return used;
}
void DevelopmentCard::setUsedTrue()  {

    this->used = true;
}

void DevelopmentCard::useDevelopmentCard(){
    this->used = true;
}
void DevelopmentCard::useDevelopmentCard(Player& p,std::string res1,std::string res2){
   if(this->getType()==4)//year of palenty
    {
        if(checkIfValidRes(res1)&&checkIfValidRes(res2))
        {
            std::map<std::string, int> get;
                
                get[res1] = 1;
                get[res2] = 1;
            p.increaseResources(get);
            this->used = true;
        }
         
    }
}
bool DevelopmentCard::checkIfValidRes(std::string res){

    if(res=="wool"||res=="wood"||res=="wheat"||res=="ore"||res=="brick")
    {
        return true;

    }
    else
        return false;

}
void DevelopmentCard::useDevelopmentCard(std::vector<ariel::Player> players,Player& p,std::string res)
{
    if(this->getType()==3)//monopoly
    {
        if(checkIfValidRes(res))
        {
            for(int i=0; i<players.size();i++)
            {
                if(players[i].get_id()!=p.get_id())
                {
                    
                    p.addResources(res,players[i].get_resources()[res]);
                    players[i].removeResources(res,players[i].get_resources()[res]);
                    this->used = true;  
                }
            }
        }
    }
}
void DevelopmentCard::useDevelopmentCard(Player& p,Road r1 , Road r2){
    if(this->getType()==2)//two free roads
    {
        p.placeRoad(r1.get_x1(),r1.get_y1(),r1.get_x2(),r1.get_y2());
        p.placeRoad(r2.get_x1(),r2.get_y1(),r2.get_x2(),r2.get_y2());
        this->used = true;
    }
}
