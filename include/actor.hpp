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
#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <memory>
#include <string>
#include <vector>

#include "vector.hpp"

class Entity;
class Actor;

class Action
{
    public:
        Action(Actor * owner, int type, wsl::Vector2i dir);
        enum Type : int
        {
            None,
            Attack,
            Move,
            Rest
        };

        void perform();
        const bool success() { return success_; }

    private:
        Actor * actor_;
        int type_;
        wsl::Vector2i dir_;
        bool success_;

        void attack_();
        void move_();
        void rest_();
};

class Actor
{
    public:
        Actor(Entity * owner = NULL, int speed = 100, int vision = 2);

        enum Flags : uint8_t
        {
            NONE = 0,
            AI = 0x002,
            ALIVE = 0x004
        };

        int mask() { return mask_; }
        bool check(int flag) { return((mask_ & flag) == flag); }
        void toggle(int flag) { mask_ ^= flag; } // Toggles a flag on or off
        void remove(int flag) { mask_ &= ~flag; } // Removes a flag (turns it off)
        void engage(int flag) { mask_ |= flag; } // Adds a flag (turns it on)

        void grantEnergy();
        int & energy() { return energy_; }
        int & speed() { return speed_; }
        int vision() { return vision_; }

        void setNextAction(int type, wsl::Vector2i dir = wsl::Vector2i()); // Passes a NEW action, nextAction_ = action;
        Action * getAction(); // Returns Action, nextAction_ = NULL
        bool update(); //IF AI, update AI component of owner (??). getAction(). !NULL ? action->perform(). action->succcess() ? DELETE action, return true
        Entity * owner() { return owner_;}

    private:
        Entity * owner_;
        int mask_;
        Action * nextAction_;
        int energy_;
        int speed_;
        int vision_;
};

#endif //ACTOR_HPP
