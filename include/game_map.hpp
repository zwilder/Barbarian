#pragma once
#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include "tile.hpp"
#include "rect.hpp"
#include "random.hpp"

class GameMap
{
    public:
        GameMap(int w, int h, int roomSizeMax = 10, int roomSizeMin = 6, int numRoomsMax = 30);
        int width() { return width_; }
        int height() { return height_; }

        int index(int x, int y) { return (x + (y * width_)); }           
        bool isBlocked(int x, int y);

        std::vector<Tile> tiles;
        std::vector<wsl::Rect> rooms;
        
    private:
        int width_;
        int height_;
        int roomSizeMax_;
        int roomSizeMin_;
        int numRoomsMax_;

        void initTiles_();
        void makeMap_();
        void createRoom_(wsl::Rect room);
        void hTunnel_(int x1, int x2, int y);
        void vTunnel_(int y1, int y2, int x);
};

#endif //GAME_MAP_HPP
