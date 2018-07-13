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

namespace wsl
{
DLList<Vector2i> bfsPath(GameMap * map, Vector2i start, Vector2i goal)
{
    std::vector< Vector2<Vector2i> > vec = breadthFirstSearch(map, start, goal);
    
    Vector2i current = goal;
    DLList<Vector2i> path(current);
    current = bfsIndex(&vec, current);
    while(current != start)
    {
        path.push(current);
        current = bfsIndex(&vec, current);
    }
    return path;
}

std::vector< Vector2<Vector2i> > breadthFirstSearch(GameMap * map, Vector2i start, Vector2i goal)
{
    /*
     * BFS uses DLList
     * Greedy BFS uses PQList
     * Both have early exit
     */
    // DLList<Vector2i> frontier(start);
    PQList<Vector2i> frontier(start, 0);

    std::vector< Vector2<Vector2i> > cameFrom;
    cameFrom.push_back( Vector2<Vector2i>(start, start) );

    while(!frontier.isEmpty())
    {
        Vector2i current = frontier.pop();

        if(current == goal)
        {
            break;
        }
        std::vector<Vector2i> neighbors = map->neighbors(current);
        for(int i = 0; i < neighbors.size(); ++i)
        {
            Vector2i next = neighbors[i];
            if(!bfsContains(&cameFrom, next))
            {
                float priority = bfsHeuristic(goal, next);
                frontier.push(next, priority);
                // frontier.push(next);
                cameFrom.push_back( Vector2<Vector2i>(next, current) );
            }
        }
    }
    return cameFrom;
}


bool bfsContains(std::vector< Vector2<Vector2i> > * vec, Vector2i id)
{
    bool success = false;
    for(int i = 0; i < vec->size(); ++i)
    {
        if(vec->at(i).x == id)
        {
            success = true;
            break;
        }
    }
    return success;
}

Vector2i bfsIndex(std::vector< Vector2<Vector2i> > * vec, Vector2i id)
{
    Vector2i result;
    for(int i = 0; i < vec->size(); ++i)
    {
        if(vec->at(i).x == id)
        {
            result = vec->at(i).y;
            break;
        }
    }
    return result;
}

float bfsHeuristic(Vector2i a, Vector2i b)
{
    float result = fabs(a.x - b.x) + fabs(a.y - b.y); // Manhattan distance
    return result;
}

} //namespace wsl
