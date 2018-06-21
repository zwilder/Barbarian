/*
* Barbarian!
* Copyright (C) 2018
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
#ifndef TILE_HPP
#define TILE_HPP

#include "console.hpp"

class Tile
{
    public:
        Tile(int mask, wsl::Glyph glyph = wsl::Glyph(' ')): mask_(mask), glyph_(glyph) { }
        
        enum Flags : int
        {
            NONE = 0,
            BLOCKS_LIGHT = 0x01,
            BLOCKS_MOVEMENT = 0x02
        };
        
        int mask() { return mask_; }
        bool checkFlag(int flag) { return((mask_ & flag) == flag); }

        bool blocksMovement() { return(checkFlag(Flags::BLOCKS_MOVEMENT)); }
        bool blocksLight() { return(checkFlag(Flags::BLOCKS_LIGHT)); }

        wsl::Glyph glyph() { return glyph_; }

    private:
        int mask_;
        wsl::Glyph glyph_;
};

#endif //TILE_HPP
