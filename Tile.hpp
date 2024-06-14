#ifndef TILE_HPP
#define TILE_HPP

#include <memory>
#include <vector>
#include <iostream>

#include <string>


class Tile {
public:
    virtual void play() = 0;
    virtual ~Tile() = default;
    std::string resource;
    std::vector<std::pair<int, int>>  cornersXY;
    int data;
    std::string get_resource() const;
    int get_data() const;

    std::vector<std::pair<int, int>> get_cornersXY() const;

};

class AgriculturalLandTile : public Tile {
public:
    void play() override;
};

class MountainsTile : public Tile {
public:
    void play() override;
};
class PastureLandTile : public Tile {
public:
    void play() override;
};
class ForestTile : public Tile {
public:
    void play() override;
};
class HillsTile : public Tile {
public:
    void play() override;
};
class DesertTile : public Tile {
public:
    void play() override;
};

class TileFactory {
public:
    static Tile* createTile(const std::string& tileType ,std::string resource ,std::vector<std::pair<int, int>>&  cornersXY ,int data);
};

#endif // TILE_HPP