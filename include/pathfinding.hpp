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
#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include <vector>

#include "vector.hpp"
#include "dllist.hpp"

class GameMap;
namespace path 
{

std::vector< wsl::Vector2<wsl::Vector2i> > breadthFirstSearch(GameMap * map, wsl::Vector2i start, wsl::Vector2i goal);

bool bfsContains(std::vector< wsl::Vector2<wsl::Vector2i> > * vec, wsl::Vector2i id);
wsl::Vector2i bfsIndex(std::vector< wsl::Vector2<wsl::Vector2i> > * vec, wsl::Vector2i id);
float bfsHeuristic(wsl::Vector2i a, wsl::Vector2i b);

// wsl::DLList<wsl::Vector2i> bfsPath(std::vector< wsl::Vector2<wsl::Vector2i> > * vec, wsl::Vector2i start, wsl::Vector2i goal);
wsl::DLList<wsl::Vector2i> bfsPath(GameMap * map, wsl::Vector2i start, wsl::Vector2i goal);
wsl::Vector2i bfsStep(GameMap * map, wsl::Vector2i start, wsl::Vector2i goal);
} // namespace wsl

#endif // PATHFINDING_HPP
