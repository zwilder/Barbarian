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
#ifndef TILE_HPP
#define TILE_HPP

#include "console.hpp"
#include "bitflag.hpp"

class Tile : public wsl::BitFlag
{
    public:
        Tile(int mask = 0, wsl::Glyph glyph = wsl::Glyph(' ')): glyph_(glyph) { set(mask); }
        
        // uint16_t goes to 0x8000 - 0001,0002,0004,0008,0010,0020,0040,0080,0100,0200,0400,0800,1000,2000,4000,8000
        // uint8_t goes to 0x100 - 001,002,004,008,010,020,040,080,100
        enum Flags : uint8_t
        {
            NONE = 0,
            BLOCKS_LIGHT = 0x001,
            BLOCKS_MOVEMENT = 0x002,
            VISIBLE = 0x004,
            EXPLORED = 0x008
        };
        
        static const Tile Floor;
        static const Tile Wall;
        
        bool blocksMovement() { return(check(Flags::BLOCKS_MOVEMENT)); }
        bool blocksLight() { return(check(Flags::BLOCKS_LIGHT)); }
        bool visible() { return(check(Flags::VISIBLE)); }
        bool explored() { return(check(Flags::EXPLORED)); }

        wsl::Glyph & glyph() { return glyph_; }

        bool operator ==(const Tile & other) { return(mask_ == other.mask_); }

    private:
        // int mask_;
        wsl::Glyph glyph_;
};

#endif //TILE_HPP
