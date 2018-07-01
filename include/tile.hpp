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

class Tile
{
    public:
        Tile(int mask = 0, wsl::Glyph glyph = wsl::Glyph(' ')): mask_(mask), glyph_(glyph) { }
        
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
        
        int mask() { return mask_; }
        bool check(int flag) { return((mask_ & flag) == flag); }
        // void toggle(int flag) { (mask_ & flag) == flag ? mask_ &= ~flag : mask_ &= flag; } // Turns a flag on or off
        void toggle(int flag) { mask_ ^= flag; } // Turns a flag on or off
        void remove(int flag) { mask_ *= ~flag; }
        void engage(int flag) { mask_ |= flag; }

        bool blocksMovement() { return(check(Flags::BLOCKS_MOVEMENT)); }
        bool blocksLight() { return(check(Flags::BLOCKS_LIGHT)); }
        bool visible() { return(check(Flags::VISIBLE)); }
        bool explored() { return(check(Flags::EXPLORED)); }

        wsl::Glyph & glyph() { return glyph_; }

        bool operator ==(const Tile & other) { return(mask_ == other.mask_); }

    private:
        int mask_;
        wsl::Glyph glyph_;
};

#endif //TILE_HPP
