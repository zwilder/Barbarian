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

#include "../include/monsters.hpp"
#include "../include/entity.hpp"
#include "../include/engine.hpp"

namespace monster
{

Entity skeleton(Engine * engine, wsl::Vector2i pos)
{
    Entity skeleton(engine, pos, wsl::Glyph('s', wsl::Color::LtGrey), "skeleton");
    skeleton.makeActor(Actor(25,8,10,0,3,35)); //s,v,mH,d,p,x
    skeleton.engage(Entity::Flags::AI);
    return skeleton;
}

Entity shamblingCorpse(Engine * engine, wsl::Vector2i pos)
{
    Entity corpse(engine, pos, wsl::Glyph('Z', wsl::Color::Red), "shambling corpse");
    corpse.makeActor(Actor(75,8,16,1,4,100)); //s,v,mH,d,p,x
    corpse.engage(Entity::Flags::AI);
    return corpse;
}

} //namespace monster
