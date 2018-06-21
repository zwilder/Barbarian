/*
* Barbarian!
* Copyright (C) 2018
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

#include <random>
#include <chrono>
#include <ctime>

namespace wsl
{
    
int randomInt(int exclusiveMax);
int randomInt(int min, int max);
double randomDouble(double exclusiveMax);
double randomDouble(double min, double max);
bool randomBool(double probability = 0.5);

} // namespace wsl

#endif // RANDOM_HPP
