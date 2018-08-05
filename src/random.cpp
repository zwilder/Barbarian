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


#include "../include/random.hpp"

namespace wsl
{

uint32_t xor128(RNGState * rng)
{
    uint32_t s = rng->w;
    uint32_t t = rng->w;
    t ^= t << 11;
    t ^= t >> 8;
    rng->w = rng->z;
    rng->z = rng->y;
    rng->y = rng->x;
    s = rng->x;
    t ^= s;
    t ^= s >> 19;
    rng->x = t;
    return t;
}

int randomInt(int max, RNGState * rng)
{
    int result = xor128(rng) % max + 1;
    return result;
}

int randomInt(int min, int max, RNGState * rng)
{
    if(min > max)
    {
        int tmp = min;
        min = max;
        max = tmp;
    }
    if(min == max)
    {
        return min;
    }

    int range = max - min;
    int result = randomInt(range + 1, rng) - 1;
    return (min + result);
}

bool randomBool(RNGState * rng)
{
    if(randomInt(2, rng) == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

} // namespace wsl
