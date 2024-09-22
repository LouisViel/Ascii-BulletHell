#include "../include/Random.h"
#include <cstdlib>
#include <ctime>



// Initialize Random Generator
void Random::init()
{
	srand((unsigned int)time(nullptr));
}

// Generate Random int in range [0, RAND_MAX]
int Random::value()
{
	return rand();
}

// Generate Random Sign (1/-1)
char Random::sign()
{
	constexpr int RAND_MAX_HALF = RAND_MAX / 2;
	return rand() < RAND_MAX_HALF ? -1 : 1;
}



// Generate Random int in range [-RAND_MAX, RAND_MAX]
int Random::valueInt()
{
	return rand() * sign();
}

// Generate Random int in range [min, max]
int Random::range(int min, int max)
{
	return rand() % (std::abs(max - min) + 1) + min;
}



// Generate Random double in range [-RAND_MAX, RAND_MAX]
double Random::valueDouble()
{
	constexpr int RAND_MAX_DOUBLE = RAND_MAX - 1;
	return (range(0, RAND_MAX_DOUBLE) + range(0.0, 1.0)) * sign();
}

// Generate Random Double in range [min, max]
double Random::range(double min, double max)
{
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}