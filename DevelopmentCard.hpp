#include "Player.hpp"
#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP


#define KNIGHT 0
#define VICTORY_POINT 1
#define ROAD_BUILDING 2
#define MONOPOLY 3
#define YEAR_OF_PLENTY 4

namespace ariel {
    class DevelopmentCard {
    private:
        int type;
        bool used;
        int playerID;

    public:
        ~DevelopmentCard();
        DevelopmentCard(int type);

        int getType() const;
        void setPlayerID(int PlayerID) ; 
        int getPlayerID()const;  

        std::string getTypeName() const;
        bool isUsed() const;
        void setUsedTrue();
        int useDevelopmentCard();
        int useDevelopmentCard(Player p,std::string res1,std::string res2);
        int useDevelopmentCard(Catan a,Player p,std::string res1);
        int useDevelopmentCard(Player p,Road r1 , Road r2){

        bool checkIfValidRes(std::string res);

    };

}
#endif 