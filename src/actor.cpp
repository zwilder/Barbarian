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

#include "../include/actor.hpp"

/*****
 * Actor Functions
 ****/
Actor::Actor(Entity * owner, int speed, int vision) : owner_(owner), speed_(speed), vision_(vision)
{
    energy_ = 0;
}

void Actor::grantEnergy()
{
    energy_ += speed_;
}
/*
void Actor::update(GameMap * map)
{
    //
}

void Actor::setNextAction(int cmd, wsl::Vector2i dir)
{
    nextAction_ = cmd;
    actionDir_ = dir; 
}

int Actor::getAction()
{
    int result = nextAction_;
    nextAction = Cmd::NONE;
    return result;
}*/
