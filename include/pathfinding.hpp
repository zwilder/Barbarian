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

#include "vector.hpp"
#include "dllist.hpp"

class GameMap;
namespace wsl
{

std::vector< Vector2<Vector2i> > breadthFirstSearch(GameMap * map, Vector2i start, Vector2i goal);

bool bfsContains(std::vector< Vector2<Vector2i> > * vec, Vector2i id);
Vector2i bfsIndex(std::vector< Vector2<Vector2i> > * vec, Vector2i id);
float bfsHeuristic(Vector2i a, Vector2i b);

DLList<Vector2i> bfsPath(std::vector< Vector2<Vector2i> > * vec, Vector2i start, Vector2i goal);
} // namespace wsl

#endif // PATHFINDING_HPP
