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
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <string>
#include "vector.hpp"
#include "console.hpp"
#include "actor.hpp"

class Engine;
class Entity
{
    public:
        Entity();
        Entity(Engine * game, wsl::Vector2i pos, wsl::Glyph glyph, std::string name);

        void makeActor(int speed, int vision);
        // Component flags
        enum Flags : uint8_t
        {
            NONE = 0,
            POS = 0x002,
            GLYPH = 0x004,
            VISION = 0X008,
            BLOCKS = 0x010,
            ACTOR = 0x020,
            AI = 0x040
        };
        
        int mask() { return mask_; }
        inline bool check(int flag) { return((mask_ & flag) == flag); }
        void toggle(int flag) { mask_ ^= flag; } // Toggles a flag on or off
        void remove(int flag) { mask_ &= ~flag; } // Removes a flag (turns it off)
        void engage(int flag) { mask_ |= flag; } // Adds a flag (turns it on)

        bool hasPos() { return check(Flags::POS); }
        bool hasGlyph() { return check(Flags::GLYPH); }
        bool hasVision() { return check(Flags::VISION); }
        bool blocks() { return check(Flags::BLOCKS); }
        
        void move(wsl::Vector2i delta);
        wsl::Vector2i pos();
        void setPos(wsl::Vector2i pos);

        wsl::Glyph & glyph();

        std::string name() { return name_; }

        Actor * actor();
        Engine * game() { return game_; }

    private:
        Engine * game_;
        int mask_;

        // Components
        wsl::Vector2i pos_; // x, y
        wsl::Glyph glyph_; // Color, symbol
        std::string name_;
        std::shared_ptr<Actor> actor_;
};
#endif //ENTITY_HPP
