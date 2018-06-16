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
