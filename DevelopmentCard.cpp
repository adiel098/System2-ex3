#include "DevelopmentCard.hpp"

#include <iostream>
#include "catan.hpp"

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
void DevelopmentCard::setPlayerID(int PlayerID)  {

    this-> playerID=playerID;
}

bool DevelopmentCard::isUsed() const {

    return used;
}
void DevelopmentCard::setUsedTrue()  {

    this->used = true;
}

int DevelopmentCard::useDevelopmentCard(){
    this->used = true;
    return this->type;
}
int DevelopmentCard::useDevelopmentCard(Player p,std::string res1,std::string res2){
   if(this->getType()==4)//year of palenty
    {
        if(checkIfValidRes(res1)&&checkIfValidRes(res2))
        {
            std::map<std::string, int> get;
                
                get[res1] = 1;
                get[res2] = 1;
            p.increaseResources(get);
        }
         
    }
}
bool DevelopmentCard::checkIfValidRes(std::string res){

    if(res=="wool"||res=="wood"||res=="wheat"||res=="ore"||res=="brick")
        return true;
    else
        return false;

}
int DevelopmentCard::useDevelopmentCard(Catan c,Player p,std::string res){
    if(this->getType()==3)//monopoly
    {
        if(checkIfValidRes(res))
        {
            for(int i=0; i<c.get_players().size();i++)
            {
                if(c.get_players()[i].get_id()!=p.get_id())
                {
                    
                    p.addResources(res,c.get_players()[i].get_resources()[res]);
                    c.get_players()[i].removeResources(res,c.get_players()[i].get_resources()[res]);

                }
            }
        }
    }
}
int DevelopmentCard::useDevelopmentCard(Player p,Road r1 , Road r2){
    if(this->getType()==2)//two free roads
    {
        p.placeRoad(r1.get_x1(),r1.get_y1(),r1.get_x2(),r1.get_y2());
        p.placeRoad(r2.get_x1(),r2.get_y1(),r2.get_x2(),r2.get_y2());

    }
}
std::string DevelopmentCard::getTypeName() const {

    switch (this->type) {

        case MONOPOLY:
            return "Monopoly";
        case YEAR_OF_PLENTY:
            return "Year of Plenty";
        case VICTORY_POINT:
            return "Victory Point";
        case KNIGHT:
            return "Knight";
        
        case ROAD_BUILDING:
            return "Road Building";
       
        default:
            return "Unknown";
    }
}