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


#include "../include/random.hpp"

namespace wsl
{

auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);

int randomInt(int exclusiveMax)
{
    std::uniform_int_distribution<int> dist(0, exclusiveMax - 1);
    return dist(mt);
}

int randomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(0, max - min);
    return dist(mt) + min;
}

double randomDouble(double exclusiveMax)
{
	std::uniform_real_distribution<double> dist(0, exclusiveMax - 1.0);
	return dist(mt);
}

double randomDouble(double min, double max)
{
	std::uniform_real_distribution<double> dist(0, max - min);
	return dist(mt);
}

bool randomBool(double probability)
{
    std::bernoulli_distribution dist(probability);
    return dist(mt);
}

} // namespace wsl
