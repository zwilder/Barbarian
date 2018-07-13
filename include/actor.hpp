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

#include <vector>
class Entity;
class Actor
{
    public:
        Actor(Entity * owner = NULL, int speed = 100, int vision = 2);

        void grantEnergy();
        int & energy() { return energy_; }
        int & speed() { return speed_; }
        int vision() { return vision_; }

    private:
        Entity * owner_;
        int energy_;
        int speed_;
        int vision_;
};

#endif //ACTOR_HPP
