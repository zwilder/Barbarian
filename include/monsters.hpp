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
#ifndef MONSTERS_HPP 
#define MONSTERS_HPP

/*
 * Eventually all these monster definitions will be moved to an external file, and then the functions for reading
 * and parsing that file will live here. For now, monsters are hard coded and these functions just return an entity
 * representing that monster. It seemed like a good idea to move their definitions here - we'll see how it pans out.
 */
#include <string>

#include "vector.hpp"
#include "color.hpp"
#include "dllist.hpp"

class Entity;
class Engine;

namespace monster
{

void loadMonsters(Engine * engine);
Entity parseEntry(std::string entry, Engine * engine);
wsl::Color parseColor(int colorInt);
Entity * pick(wsl::DLList<Entity> * list, std::string name);

Entity player(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));

Entity skeleton(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));
Entity shamblingCorpse(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));

} // namespace monster

#endif //MONSTERS_HPP
