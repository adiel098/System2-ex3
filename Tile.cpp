//id: 207988213 email:haleviadiel@gmail.com
#ifndef TILE_HPP
#define TILE_HPP
#include <string>
#include <vector>
#include <memory>
#include "Tile.hpp"


namespace ariel
{
    class Tile 
    {
    public:
        virtual void play() = 0;
        virtual ~Tile() = default;
        std::string resource;
        std::vector<std::pair<int, int>>  cornersXY;
        int data;
         std::vector<std::pair<int, int>> get_cornersXY() const
        {
            return cornersXY;
            
        }
        std::string get_resource() const
        {
            return resource;
        
        }
        int get_data() const
        {
            return data;
        
        }
    };
    
   

    class AgriculturalLandTile : public Tile 
    {
    public:
        void play() override {
            // Logic for knight card
        }
    };

    class MountainsTile : public Tile 
    {
    public:
        void play() override {
            // Logic for victory point card
        }
    };
      class PastureLandTile : public Tile 
    {
    public:
        void play() override {
            // Logic for victory point card
        }
    };
      class ForestTile : public Tile 
    {
    public:
        void play() override {
            // Logic for victory point card
        }
    };
      class HillsTile : public Tile 
    {
    public:
        void play() override {
            // Logic for victory point card
        }
    };
     class DesertTile : public Tile 
    {
    public:
        void play() override {
            // Logic for victory point card
        }
    };

    class TileFactory 
    {
    public:
        static Tile* createTile(const std::string& tileType ,std::string resource ,std::vector<std::pair<int, int>>&  cornersXY ,int data) {
            if (tileType == "AgriculturalLand") 
            {
                 
                auto tile = new AgriculturalLandTile();
                tile->resource = resource;
                tile->cornersXY = cornersXY;
                tile->data = data;
                return tile;
            } 
            else if (tileType == "Mountains") 
            {
                auto tile = new MountainsTile();
                tile->resource = resource;
                tile->cornersXY = cornersXY;
                tile->data = data;
                return tile;
            }
            else if (tileType == "PastureLand") 
            {
                auto tile = new PastureLandTile();
                tile->resource = resource;
                tile->cornersXY = cornersXY;
                tile->data = data;
                return tile;
            }
            else if (tileType == "Forest") 
            {
                auto tile =  new ForestTile();
                tile->resource = resource;
                tile->cornersXY = cornersXY;
                tile->data = data;
                return tile;
            }
            else if (tileType == "Hills") 
            {
                auto tile = new HillsTile();
                tile->resource = resource;
                tile->cornersXY = cornersXY;
                tile->data = data;
                return tile;
            }
            else if (tileType == "Desert") 
            {
                auto tile = new DesertTile();
                tile->resource = resource;
                tile->cornersXY = cornersXY;
                tile->data = data;
                return tile;
            }
            // Add more card types as needed
            return nullptr;
        }
    };

}
#endif