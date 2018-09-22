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

#include <memory>

#include "vector.hpp"
#include "dllist.hpp"
#include "tile.hpp"

// namespace wsl
// {
class Engine;
// }

/*
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
        Frame(const Frame & other);
        Frame & operator =(Frame & other)
        {
            swap(*this, other);
            return * this;
        }
        friend void swap(Frame & a, Frame & b)
        {
            using std::swap;
            swap(a.tiles, b.tiles);
            swap(a.duration, b.duration);
        }
        std::unique_ptr< wsl::DLList<AnimationTile> > tiles;
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
        Animation(Animation & other); //Copy constructor
        Animation & operator =(Animation & other)
        {
            swap(*this, other);
            return *this;
        }
        friend void swap(Animation & a, Animation & b)
        {
            using std::swap;
            swap(a.lastUpdate, b.lastUpdate);
            swap(a.nextUpdate, b.nextUpdate);
            swap(a.frames, b.frames);
        }
        void update(int dt);
        void draw(wsl::Console * console);

        std::unique_ptr< wsl::DLList<Frame> > frames;
        int lastUpdate;
        int nextUpdate;
};
*/
class AnimationTile
{
    public:
        AnimationTile(wsl::Glyph g = wsl::Glyph(), wsl::Vector2i p = wsl::Vector2i()) : glyph(g), pos(p) { }
        wsl::Glyph glyph;
        wsl::Vector2i pos;
};

class AnimationFrame : public wsl::BitFlag
{
    public:

        enum Flags : uint8_t
        {
            NONE,
            APPLY_FG = 0x002,
            APPLY_BG = 0x004,
            APPLY_GLYPH = 0x008,
            ALL_VIS = 0x010,
            LEAVE_TILE = 0x020
        };
        AnimationFrame() { duration = 0; }
        std::vector<AnimationTile> tiles;
        int duration;
};

class Animation : public wsl::BitFlag
{
    public:
        Animation();
        enum Flags : uint8_t
        {
            NONE = 0,
            DEAD = 0x002,
            LOOP = 0x004
        };

        void update(int dt);
        void draw(Engine * engine);

        std::vector<AnimationFrame> frames;
        int currentFrame;
        int lastUpdate;
        int nextUpdate;
};

namespace Animated
{
Animation explosion(wsl::Vector2i origin, int radius);
Animation projectile(wsl::Glyph glyph, wsl::Vector2i origin, wsl::Vector2i destination);
Animation beam(wsl::Vector2i origin, wsl::Vector2i destination, wsl::Color color);
Animation screenflash(wsl::Vector2i screenDimensions, wsl::Color color);
Animation lightning(wsl::Vector2i origin, wsl::Vector2i destination);
Animation fireball(int radius, wsl::Vector2i origin, wsl::Vector2i destination);
Animation firebolt(wsl::Vector2i origin, wsl::Vector2i destination);
}
#endif // ANIMATION_HPP
