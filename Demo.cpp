/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "Player.hpp"
#include "board.hpp"
using namespace std;
using namespace ariel;

int main()
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    Board board = catan.getBoard(); // get the board of the game.
   
    p1.placeSettlement(5,0);
    p1.placeRoad(5,0,6,0 );
    
    p1.placeSettlement(0,3);
    p1.placeRoad(0, 3, 1,2); // p1 chooses Forest, hills, Agricultural Land, Desert with numbers 5, 6, 3, 4.

    
    p2.placeSettlement(3,3);
    p2.placeRoad(3,3,3,4);
    try
    {
        p3.placeSettlement(3,3); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    
    p2.placeSettlement(3,11);
    p2.placeRoad(3,11,2,10); // p2 chooses Mountains, Pasture Land, and Forest with numbers 4, 9, 5.

    
    p3.placeSettlement(2,32);
    p3.placeRoad(2,3,1,4);
    
    p3.placeSettlement(9,4);
    p3.placeRoad(9,4,10,5); // p3 chooses Mountains, Pasture Land, Agricultural Land, Pasture Land with numbers 3, 8, 3, 9.

    // p1 has wood,bricks, and wheat, p2 has wood, ore, and wool, p3 has ore, wool, wheat.
    p1.rollDice();                                    // Lets say it's print 4. Then, p2 gets ore from the mountations.
    p1.endTurn();                                     // p1 ends his turn.

    p2.rollDice(); // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.endTurn();  // p2 ends his turn.

    p3.rollDice(); // Lets say it's print 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
    p3.endTurn();  // p3 ends his turn.

    try
    {
        p2.rollDice(); // p2 tries to roll the dice again, but it's not his turn.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    p1.rollDice(); 
    std::map<std::string, int> give;
    give["wood"]  =1;
    std::map<std::string, int> get;
    get["brick"]  =1;
                       // Lets say it's print 6. Then, p1 gets bricks from the hills.
    p1.trade(p2,give,get); // p1 trades 1 wood for 1 brick with p2.
    p1.endTurn();                        // p1 ends his turn.

    p2.rollDice();           // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.buyDevelopmentCard(); // p2 buys a development card. Lets say it is a bonus points card.
    p2.endTurn();            // p2 ends his turn.

    p1.printPoints(); // p1 has 2 points because it has two settelments.
    p2.printPoints(); // p2 has 3 points because it has two settelments and a bonus points card.
    p3.printPoints(); // p3 has 2 points because it has two settelments.

    catan.printWinner(); // Should print None because no player reached 10 points.
}