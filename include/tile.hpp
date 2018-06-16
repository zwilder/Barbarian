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
