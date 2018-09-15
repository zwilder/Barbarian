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
#include "dllist.hpp"
#include "tile.hpp"

namespace wsl
{
class Console;
}

class AnimationTile
{
    public:
        AnimationTile(wsl::Glyph t = wsl::Glyph(' '), wsl::Vector2i p = wsl::Vector2i(0,0));
        wsl::Glyph tile;
        wsl::Vector2i pos;
};

class Frame
{
    public:
        Frame(wsl::DLList<AnimationTile> t = wsl::DLList<AnimationTile>(), int d = 0);
        wsl::DLList<AnimationTile> tiles;
        int duration; // in milliseconds
};

class Animation : public wsl::BitFlag
{
    public:
        enum Flags : uint8_t
        {
            NONE = 0,
            APPLY_BG = 0x002,
            APPLY_FG = 0x004,
            APPLY_GLYPH = 0x008,
            DEAD = 0x010,
            LOOP = 0x020
        };
        Animation(wsl::DLList<Frame> f = wsl::DLList<Frame>());
        void update(int dt);
        void draw(wsl::Console * console);

        wsl::DLList<Frame> frames;
        int lastUpdate;
        int nextUpdate;
};

namespace Animated
{
// Animation explosion(wsl::Vector2i origin, int radius);
Animation projectile(wsl::Glyph glyph, wsl::Vector2i origin, wsl::Vector2i destination);
// Animation fireball(wsl::Vector2i origin, wsl::Vector2i destination);
}
#endif // ANIMATION_HPP
