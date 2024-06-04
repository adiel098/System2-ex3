#ifndef BOARD_HPP
#define BOARD_HPP
#include <string>


namespace ariel
{

    class Tile {
    
    private:
        std::string type;
        std::string resource;
        std::vector<std::pair<int, int>>  cornersXY;
        int data;


    public:
        Tile();
        Tile(std::string type ,std::string resource ,std::vector<std::pair<int, int>> cornersXY,int data );
        std::string get_type() const;
        std::string get_resource() const;
        std::vector<std::pair<int, int>> get_cornersXY() const;

        int get_data() const;
    };
    class Settlement {
    
    private:
        int type;
        int playerID;
        int x;
        int y;



    public:
        Settlement();
        Settlement(int type,int ownerID , int x, int y);
        int get_type() const;
        int get_playerID() const;
        int get_x() const;
        int get_y() const;
        bool Settlement::validSettlement(Board b,int playerID,int type,int x,int y);




    };

    class Road {
    
    private:
        int playerID;
        int x1,y1,x2,y2;


    public:
        Road();
        Road(int playerID,int x1,int y1, int x2, int y2);
        int get_playerID() const;
        int Road::get_x1() const;
        int Road::get_x2() const;
        int Road::get_y1() const;
        int Road::get_y2() const;
        void Road::setRoad(Board b,int playerID,int x1,int y1,int x2,int y2) ;  
        bool Road::validRoad(Board b,int playerID,int x1,int y1,int x2,int y2);
        bool Road::operator==(Road& other)const;



    };
    class DevelopmentCard {
        
        private:
            std::string type;
            bool used;
            

        public:
            DevelopmentCard();
            DevelopmentCard(std::string type);
            std::string get_type() const;

            

    };

    class Board 
        {

        private:
            //constructors
            std::vector<Tile> tiles;
            std::vector<Settlement> settlements;
            std::vector<Road> roads;
            std::vector<DevelopmentCard> developmentCards;
        public:
            Board();
            Board(std::string name);
            void Board::initializeBoard(std::vector<Tile>& tiles,std::vector<Settlement>& settlements, std::vector<Road>& roads,std::vector<DevelopmentCard>& developmentCards) ;
            static bool Board::isXYInBoard(int x, int y);
            std::vector<Road> Board::get_roads() const;
            std::vector<DevelopmentCard> Board::get_developmentCards() const;
            std::vector<Settlement> Board::get_settlements() const;
            std::vector<Settlement> Board::get_settlements_by_id(int playerID) const ;
            std::vector<Road> Board::get_roads_by_id(int playerID) const;
            std::vector<Tile> Board::get_tiles() const;


            //fields
            
 
            //functions
            



        
        };
}
#endif