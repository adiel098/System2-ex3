//id: 207988213 email:haleviadiel@gmail.com
#ifndef TILE_HPP
#define TILE_HPP

#include <memory>
#include <vector>
#include <iostream>

#include <string>
#define AgriculturalLand 0
#define Mountains 1
#define PastureLand 2
#define Forest 3
#define Hills 4
namespace ariel {

class Tile {
public:
        ~Tile();
        Tile(std::string tileType ,std::string resource ,std::vector<std::pair<int, int>>&  cornersXY ,int data);
    std::string resource,type;
    std::vector<std::pair<int, int>>  cornersXY;
    int data;
    std::string get_resource() const;
    int get_data() const;

    std::vector<std::pair<int, int>> get_cornersXY() const;

};

}

#endif // TILE_HPP