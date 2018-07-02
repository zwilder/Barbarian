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

#include <cmath>
#include <algorithm>
#include "../include/fov.hpp"

namespace fov
{

void visible(std::vector<wsl::Vector2i> * results, GameMap * map, Entity * entity)
{
    results->clear();
    if(!entity->hasPos())
    {
        // Entity has no position
        return;// results;
    }

    results->push_back(entity->pos());

    if(!entity->hasVision())
    {
        // Entity has no vision - funny, this could be an easy way to take away the characters sight!
        return;// results;
    }

    int r = entity->vision(); // [r]ange
    int xO = entity->pos().x;
    int yO = entity->pos().y;

    for(int x = xO - r; x < xO + r; ++x)
    {
        for(int y = yO - r; y < yO + r; ++y)
        {
            if(sqrt(pow(x - xO, 2) + pow(y - yO, 2)) <= r)
            {
                bhline(xO,yO,x,y,results,map);
            }
        }
    }
}

void bhline(int xO, int yO, int xF, int yF, std::vector<wsl::Vector2i> * results, GameMap * map)
{
    int dX = abs(xF - xO);
    int dY = abs(yF - yO);

    if(dX >= dY)
    {
        int e = dY - dX; // [e]rror
        int j = yO;

        if(xO < xF)
        {
            // Octants 1,2
            for(int i = xO; i <= xF; ++i)
            {
                add(results, wsl::Vector2i(i,j));
                if(map->tiles[map->index(i,j)].blocksLight())
                {
                    break;
                }
                if((e >= 0) && (yF >= yO))
                {
                    // 1
                    j += 1;
                    e -= dX;
                }
                else if((e >= 0) && (yF < yO))
                {
                    // 2
                    j -= 1;
                    e -= dX;
                }
                e += dY;
            }
        }
        else if(xO > xF)
        {
            // Octants 5,6
            for(int i = xO; i >= xF; --i)
            {
                add(results, wsl::Vector2i(i, j));
                if(map->tiles[map->index(i,j)].blocksLight())
                {
                    break;
                }
                if((e >= 0) && (yF >= yO))
                {
                    // 6
                    j += 1;
                    e -= dX;
                }
                else if((e >= 0) && (yF < yO))
                {
                    // 5
                    j -= 1;
                    e -= dX;
                }
                e += dY;
            }
        }
    }
    else if (dX < dY)
    {
        int e = dX - dY; // [e]rror
        int i = xO;
        if(yO < yF)
        {
            // Octants 7,8
            for(int j = yO; j <= yF; ++j)
            {
                add(results, wsl::Vector2i(i,j));
                if(map->tiles[map->index(i,j)].blocksLight())
                {
                    break;
                }
                if((e >= 0) && (xF >= xO))
                {
                    // 8
                    i += 1;
                    e -= dY;
                }
                else if((e >= 0) && (xF < xO))
                {
                    // 7
                    i -= 1;
                    e -= dY;
                }
                e += dX;
            }
        }
        else if(yO > yF)
        {
            // Octants 3,4
            for(int j = yO; j >= yF; --j)
            {
                add(results, wsl::Vector2i(i,j));
                if(map->tiles[map->index(i,j)].blocksLight())
                {
                    break;
                }
                if((e >= 0) && (xF >= xO))
                {
                    // 3
                    i += 1;
                    e -= dY;
                }
                else if((e >= 0) && (xF < xO))
                {
                    // 4
                    i -= 1;
                    e -= dY;
                }
                e += dX;
            }
        }
    }
}

void add(std::vector<wsl::Vector2i> * vector, wsl::Vector2i element)
{
    // Helper function so I don't have to type this conditional repeatedly
    if(!contains(vector, element))
    {
        vector->push_back(element);
    }
}

bool contains(std::vector<wsl::Vector2i> * vector, wsl::Vector2i element)
{
    // Helper function so I don't have to... wait, I already typed this comment above.
    bool success = false;
    if(std::find(vector->begin(), vector->end(), element) != vector->end())
    {
        success = true;
    }
    else
    {
        success = false;
    }
    return success;
}

} // namespace fov
