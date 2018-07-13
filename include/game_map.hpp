/*
* Barbarian!
* Copyright (C) Zach Wilder 2018
* 
* This file is a part of Barbarian!
*
* Barbarian! is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Barbarian! is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Barbarian!.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include "tile.hpp"
#include "rect.hpp"
#include "entity.hpp"

class Engine;
class GameMap
{
    public:
        GameMap(Engine * owner, int w, int h, int roomSizeMax = 10, int roomSizeMin = 6, int numRoomsMax = 30);
        // static std::array<wsl::Vector2i, 4> DIRS;
        static std::array<wsl::Vector2i, 8> DIRS;
        int width() { return width_; }
        int height() { return height_; }

        inline int index(int x, int y) { return (x + (y * width_)); }           
        bool isBlocked(int x, int y);

        Tile & tileAt(int x, int y);
        Tile & tileAt(wsl::Vector2i pos);
        Entity * entityAt(wsl::Vector2i pos, std::vector<Entity> * entityList);
        Entity * entityAt(int x, int y, std::vector<Entity> * entityList);
        
        void placeEntities(int maxPerRoom);
        
        std::vector<wsl::Vector2i> neighbors(wsl::Vector2i start);

        std::vector<Tile> tiles;
        std::vector<wsl::Rect> rooms;
        
    private:
        Engine * owner_;
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

        bool inBounds_(wsl::Vector2i pos);
};

#endif //GAME_MAP_HPP
