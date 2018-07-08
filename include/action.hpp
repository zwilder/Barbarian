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
#ifndef ACTION_HPP
#define ACTION_HPP

#include "vector.hpp"

class Entity;
class Tile;
class Action
{
    public:
        Action();
        Action(int mask, Entity * actor, Entity * other, Tile * tile, wsl::Vector2i pos);

        enum Flags : uint16_t
        {
            NONE = 0,
            SUCCESS = 0x0002,
            ATTACK = 0x0004,
            WALK = 0x0008,
            REST = 0x0010,
        };

        int mask() { return mask_; }
        bool check(int flag) { return((mask_ & flag) == flag); }
        void toggle(int flag) { mask_ ^= flag; } // Turns a flag on or off
        void remove(int flag) { mask_ &= ~flag; }
        void engage(int flag) { mask_ |= flag; }

        void perform();
        bool success() { return check(Flags::SUCCESS); }
        bool hasAlternate() { return (alternateMask_ == Flags::NONE); }

    private:
        void attack_();
        void move_();
        void rest_();

        int mask_;
        int alternateMask_;

        Entity * actor_;
        Entity * other_;
        Tile * tile_;
        wsl::Vector2i pos_;
};

#endif //ACTION_HPP
