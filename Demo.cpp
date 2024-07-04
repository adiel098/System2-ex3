/**
 * Demo file for Ex3.
 *
 *///id: 207988213 email:haleviadiel@gmail.com
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"   // Include Catan header
#include "Player.hpp" // Include Player header

using namespace std;
using namespace ariel;

int main()
{
    ariel::Player p1("Alice", nullptr);
    ariel::Player p2("Bob", nullptr);
    ariel::Player p3("Charlie", nullptr);

    ariel::Catan game(p1, p2, p3);

    p1.set_game(&game);
    p2.set_game(&game);
    p3.set_game(&game);
    game.setPlayer(0, p1);
    game.setPlayer(1, p2);
    game.setPlayer(2, p3);

    // Starting of the game. Every player places two settlements and two roads.
    game.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Alice.

  // Player 1's turn


    //should success
    p1.placeSettlement(4, 1);
    p1.placeRoad(4, 1, 5, 0);
    p1.placeSettlement(6, 0);
    p1.placeRoad(6, 0, 7, 1); 
    p1.addResources("wood",500);
    p1.addResources("wheat",500);
    p1.addResources("wool",500);
    p1.addResources("brick",500);
    p1.addResources("ore",500);
    //try to place more than 2 roads/settlements
    p1.placeSettlement(2, 2);
    p1.placeRoad(2, 2, 3, 1);
    

    p1.printResources();

    p1.addResources("ore",3);
    p1.addResources("wood",5);

    p1.printResources();
    p1.buyDevelopmentCard();//buy knight
    p1.buyDevelopmentCard();//buy knight
    p1.buyDevelopmentCard();//buy knight
    p1.buyDevelopmentCard();//buy victory point
    p1.buyDevelopmentCard();//buy 2road
    p1.buyDevelopmentCard();//buy monopoly
    p1.buyDevelopmentCard();//buy year of plenty


   

    std::cout<<game.get_players()[0].get_player_cards().size()<<std::endl;
    std::cout<<game.get_players()[0].get_player_cards()[0]->getType()<<std::endl;
    std::cout<<game.get_players()[0].get_player_cards()[1]->getType()<<std::endl;
    std::cout<<game.get_players()[0].get_player_cards()[2]->getType()<<std::endl;
    std::cout<<game.get_players()[0].get_player_cards()[3]->getType()<<std::endl;
    std::cout<<game.get_players()[0].get_player_cards()[4]->getType()<<std::endl;
    std::cout<<game.get_players()[0].get_player_cards()[5]->getType()<<std::endl;
    std::cout<<game.get_players()[0].get_player_cards()[6]->getType()<<std::endl;

   

    p1.endTurn();

    // Player 2's turn
    p2.placeSettlement(3, 3);
    p2.placeRoad(3, 3, 3, 5);
    p2.placeSettlement(0, 5);
    p2.placeRoad(0, 5, 1, 4);
    p2.printResources();

    p2.addResources("ore",3);
    p2.printResources();

    p2.trade(p1,{{"ore",3}},{{"wood",3}});//should success
    p2.trade(p1,{{"ore",3}},{{"wood",3}});//should failed

    p2.printResources();

    p2.endTurn();

    // Player 3's turn


    //should fail 
    p3.placeSettlement(3, 3); // p3 tries to place a settlement in the same location as p2.
    p3.placeSettlement(7, 1); //to close to other settlemnts (less than 2 roads)
    p3.placeRoad(7, 1, 8, 1); //Invalid position or no connected road.
    p3.placeSettlement(8, 8); //Position not in the baord.
    p3.placeRoad(6, 0, 7, 1); //exist road already

    //should success
    p3.placeSettlement(6, 8);
    p3.placeRoad(6, 8, 7, 7);
    p3.placeSettlement(4, 9);
    p3.placeRoad(4, 9, 5, 8);


    p3.printResources();
    p3.endTurn();

    // Player 1's additional settlements and roads
    p1.printResources();
    p1.rollDice();
    p1.rollDice();
    p1.rollDice();
    p1.rollDice();

    p1.addResources("wood",500);
    p1.addResources("wheat",500);
    p1.addResources("wool",500);
    p1.addResources("brick",500);
    p1.addResources("ore",500);
    p1.buySettlement(8,1); // will fail cause not road connected

    p1.buyRoad(7, 1, 8, 1); //  buy road so now 2 road in row
    p1.buyRoad(8, 1, 9, 2); // buy more one  road so now 3 road in row

    p1.buySettlement(9,2);// success able buy settlement




    p1.printResources();

    p1.addResources("ore",3);
    p1.addResources("wheat",2);
    p1.printResources();

    p1.buyTown(4, 1); // p1 tries to place a settlement in the same location as p2.

    p1.buyTown(4, 1); // should failed
    p1.buyTown(0, 1); // should failed

  

  

    p1.useKnight();
    p1.useKnight();//will not work already used develop card


    p1.printResources();
    p2.printResources();
    p3.printResources();
    p1.useMonopoly("wool");
    p1.printResources();
    p2.printResources();
    p3.printResources();


    p1.useYearOfPlenty("wool","wood");
    p1.printResources();

    p1.useYearOfPlenty("wool","wood");//dont have card


    Road r1= Road(p1.get_id(),1,1,2,2);
    Road r2= Road(p1.get_id(),1,1,2,2);

    p1.useTwoFreeRoads(r1,r2);//should not work wrong locations
    p1.useKnight();
    p1.endTurn();

    // Player 2's additional settlements and roads
    p2.placeSettlement(5, 6);
    p2.placeRoad(5, 6, 6, 4);
    p2.printResources();
    p2.endTurn();

    // Player 3's additional settlements and roads
    p3.placeSettlement(6, 8);
    p3.placeRoad(6, 8, 7, 7);
    p3.printResources();

    p3.endTurn();
    p1.useKnight();//use the second time

    p1.endTurn();
    p2.endTurn();
    p3.endTurn();

    p1.useKnight();//use the third time
    
    p1.endTurn();



    game.printAllBuildings();
    game.printAllPlayerPoints();
    return 0;
}
