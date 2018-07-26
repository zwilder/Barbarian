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

#include "../include/pathfinding.hpp"
#include "../include/game_map.hpp"
#include "../include/pqlist.hpp"

/*
 * A lot of this is my adaptation of the Red Blob Games pathfinding at https://www.redblobgames.com/pathfinding/a-star/introduction.html
 * std::priority_queue and std::map didn't want to play nicely with my classes - I can't figure out why, but boy does it piss off the compiler!
 * At least this gave me an opportunity to use classes I've already written in new ways!
 *
 * std::map is replaced here by using a vector of Vector2<Vector2i> - each element looks like ((x,y),(x,y)). The bfsContains function looks through the 
 * vector of vectors and returns true if the id (left side pair) is in the vector. bfsIndex looks through the vector for an id (left side pair) and
 * returns the right side pair as the value.
 */

namespace path
{
wsl::DLList<wsl::Vector2i> bfsPath(GameMap * map, wsl::Vector2i start, wsl::Vector2i goal)
{
    std::vector< wsl::Vector2<wsl::Vector2i> > vec = breadthFirstSearch(map, start, goal);
    
    wsl::Vector2i current = goal;
    wsl::DLList<wsl::Vector2i> path(current);
    current = bfsIndex(&vec, current);
    while(current != start)
    {
        path.push(current);
        current = bfsIndex(&vec, current);
    }
    return path;
}

wsl::Vector2i bfsStep(GameMap * map, wsl::Vector2i start, wsl::Vector2i goal)
{
    wsl::Vector2i result = bfsPath(map, start, goal).popFront();
    return result;
}

std::vector< wsl::Vector2<wsl::Vector2i> > breadthFirstSearch(GameMap * map, wsl::Vector2i start, wsl::Vector2i goal)
{
    /*
     * BFS uses DLList
     * Greedy BFS uses wsl::PQList
     * Both have early exit
     */
    // DLList<Vector2i> frontier(start);
    wsl::PQList<wsl::Vector2i> frontier(start, 0);

    std::vector< wsl::Vector2<wsl::Vector2i> > cameFrom;
    cameFrom.push_back( wsl::Vector2<wsl::Vector2i>(start, start) );

    while(!frontier.isEmpty())
    {
        wsl::Vector2i current = frontier.pop();

        if(current == goal)
        {
            break;
        }
        std::vector<wsl::Vector2i> neighbors = map->neighbors(current);
        for(size_t i = 0; i < neighbors.size(); ++i)
        {
            wsl::Vector2i next = neighbors[i];
            if(!bfsContains(&cameFrom, next))
            {
                float priority = bfsHeuristic(goal, next);
                frontier.push(next, priority);
                // frontier.push(next);
                cameFrom.push_back( wsl::Vector2<wsl::Vector2i>(next, current) );
            }
        }
    }
    return cameFrom;
}


bool bfsContains(std::vector< wsl::Vector2<wsl::Vector2i> > * vec, wsl::Vector2i id)
{
    bool success = false;
    for(size_t i = 0; i < vec->size(); ++i)
    {
        if(vec->at(i).x == id)
        {
            success = true;
            break;
        }
    }
    return success;
}

wsl::Vector2i bfsIndex(std::vector< wsl::Vector2<wsl::Vector2i> > * vec, wsl::Vector2i id)
{
    wsl::Vector2i result;
    for(size_t i = 0; i < vec->size(); ++i)
    {
        if(vec->at(i).x == id)
        {
            result = vec->at(i).y;
            break;
        }
    }
    return result;
}

float bfsHeuristic(wsl::Vector2i a, wsl::Vector2i b)
{
    float result = fabs(a.x - b.x) + fabs(a.y - b.y); // Manhattan distance
    return result;
}

void bhline(wsl::Vector2i start, wsl::Vector2i finish, std::vector<wsl::Vector2i> * results)
{
    bhline(start.x, start.y, finish.x, finish.y, results);
}

void bhline(int xO, int yO, int xF, int yF, std::vector<wsl::Vector2i> * results)
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
} //namespace wsl
