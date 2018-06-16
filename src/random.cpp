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
