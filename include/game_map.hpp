#pragma once
#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include "tile.hpp"

class GameMap
{
    public:
        GameMap(int w, int h);
        int width() { return width_; }
        int height() { return height_; }

        int index(int x, int y) { return (x + (y * width_)); }           

        std::vector<Tile> tiles;
        
    private:
        int width_;
        int height_;

        void initTiles_();
};

#endif //GAME_MAP_HPP
