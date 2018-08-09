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
#ifndef ITEMS_HPP
#define ITEMS_HPP

/*
 * Eventually all these item definitions will be moved to an external file, and then the functions for reading
 * and parsing that file will live here. For now, items are hard coded and these functions just return an entity
 * representing that item. It seemed like a good idea to move their definitions here - we'll see how it pans out.
 */

#include "vector.hpp"

class Entity;
class Engine;

namespace item
{

Entity healingPotion(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));
Entity lightningScroll(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));
Entity fireballScroll(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));
Entity fireboltScroll(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));
Entity woodenShield(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));
Entity battleAxe(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));
Entity dagger(Engine * engine, wsl::Vector2i pos = wsl::Vector2i(0,0));

} //namespace item

#endif //ITEMS_HPP
