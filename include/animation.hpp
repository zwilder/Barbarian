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
#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "vector.hpp"
#include "tile.hpp"

class Engine;

class AnimationTile
{
    public:
        Tile tile;
        wsl::Vector2i pos;
};

class Frame
{
    public:
        wsl::DLList<AnimationTile> tiles;
        int duration;
};

class Animation : public wsl::BitFlag
{
    public:
        enum Flags : uint8_t
        {
            DRAW_BG = 0x002,
            DRAW_FG = 0x004,
            DRAW_GLYPH = 0x008
        };
        Animation(wsl::DLList<Frame> f = wsl::DLList<Frame>());
        void update(int dt);
        void draw(Engine * engine);

        wsl::DLList<Frame> frames;
        int lastUpdate;
        int nextUpdate;
};

#endif // ANIMATION_HPP
