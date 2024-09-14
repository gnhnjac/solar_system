#include "utils.hpp"
#include <cstdlib>

float fremap(const float value, const float low1, const float high1, const float low2, const float high2)
{

	return low2 + (value - low1) * (high2 - low2) / (high1 - low1);

}

float frand(const float min, const float max)
{

	return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));

}