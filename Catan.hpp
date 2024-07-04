#ifndef CATAN_HPP
#define CATAN_HPP

#include "Board.hpp"  // Ensure this is included before declaring the Board variable
#include "Player.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <random>

namespace ariel {
    class Board;
    class Player; // Forward declaration of the Player class

    class Catan {
    private:
        Board* b; // Ensure Board is included properly
        int turn;
        int winner;
        int kingOfKnightsCount;
        int kingOfKnightsID;
        std::vector<Player> players;

    public:
        Catan(Player& p1, Player& p2, Player& p3);
        Catan();

        Catan& getCatan();

        std::string get_name() const;
        void ChooseStartingPlayer();
        void printWinner();
        void checkKingOfKnights();
        Board& getBoard();
        int getTurn() const;
        void setTurn(int turn);
        std::vector<Player>& get_players();
        void updateResourcesOfPlayers(int diceNumber);
        void updateResPlayerFirstTurn(int id) ;

        bool checkWinner();
        void nextTurn();
        void printAllBuildings() const ;
        void printAllPlayerPoints() const ;
        void calculateAndUpdatePoints() ;

        // New methods to set and get players
        void setPlayer(int index, Player& player);
        Player& getPlayer(int index);
    };
    class WinnerException : public std::exception {
public:
    explicit WinnerException(const std::string& message) : message_(message) {}
    virtual const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};
}

#endif // CATAN_HPP
