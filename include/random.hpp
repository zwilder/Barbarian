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
#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdint>

namespace wsl
{

struct RNGState
{
//    362436069,521288629,88675123
    RNGState(uint32_t a = 0, uint32_t b = 362436069, uint32_t c = 521288629, uint32_t d = 88675123) : x(a), y(b), z(c), w(d) { }
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t w;
};

uint32_t xor128(RNGState * rng);
int randomInt(int min, int max, RNGState * rng);
int randomInt(int max, RNGState * rng);
bool randomBool(RNGState * rng);

// int randomInt(int exclusiveMax);
// int randomInt(int min, int max);
// double randomDouble(double exclusiveMax);
// double randomDouble(double min, double max);
// bool randomBool(double probability = 0.5);

} // namespace wsl

#endif // RANDOM_HPP
