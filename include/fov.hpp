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
#ifndef FOV_HPP
#define FOV_HPP

#include "game_map.hpp"
#include "entity.hpp"

namespace fov
{

    // std::vector<wsl::Vector2i> visible(GameMap * map, Entity * entity); 
    void visible(std::vector<wsl::Vector2i> * visible, GameMap * map, Entity * entity); 
    void bhline(int xO, int yO, int xF, int yF, std::vector<wsl::Vector2i> * results, GameMap * map);
    void add(std::vector<wsl::Vector2i> * vector, wsl::Vector2i element);
    bool contains(std::vector<wsl::Vector2i> * vector, wsl::Vector2i element);

}// namespace fov

#endif // FOV_HPP
