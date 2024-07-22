//id: 207988213 email:haleviadiel@gmail.com
#include "Player.hpp"
#include "Catan.hpp"
#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP


#define KNIGHT 0
#define VICTORY_POINT 1
#define ROAD_BUILDING 2
#define MONOPOLY 3
#define YEAR_OF_PLENTY 4

namespace ariel {
        class Player;  // Forward declaration
            class Road;  // Forward declaration


    class DevelopmentCard {
    private:
        int type;
        bool used;
        int playerID;

    public:
        ~DevelopmentCard();
        DevelopmentCard(int type);

        int getType() const;
        std::string getTypeName() const;
        void setPlayerID(int PlayerID) ; 
        int getPlayerID()const;  

        bool isUsed() const;
        void setUsedTrue();
        void useDevelopmentCard();
        void useDevelopmentCard(Player& p,std::string res1,std::string res2);
        void useDevelopmentCard(std::vector<ariel::Player> players,Player& p,std::string res1);
        void useDevelopmentCard(Player& p,Road r1 , Road r2);

        bool checkIfValidRes(std::string res);

    };

}
#endif 