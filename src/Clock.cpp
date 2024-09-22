#include "../include/Clock.h"

Clock* Clock::singleton = nullptr;

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

const float& Clock::getDeltaTime()
{
	return singleton->deltaTime;
}

Clock::Clock() : deltaTime(0)
{
	QueryPerformanceCounter(&lastUpdateTime);
	LARGE_INTEGER li_freq;
	QueryPerformanceFrequency(&li_freq);
	freq = li_freq.QuadPart;
	freq /= 1000;
	QueryPerformanceCounter(&lastUpdateTime);
	singleton = this;
}

Clock::~Clock()
{
	singleton = nullptr;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void Clock::updateDeltaTime()
{
	LARGE_INTEGER timeNow;
	QueryPerformanceCounter(&timeNow);
	LONGLONG elapsedLong = timeNow.QuadPart - lastUpdateTime.QuadPart;
	lastUpdateTime = timeNow;

	float elapsed = (float)elapsedLong / (float)freq;
	deltaTime = elapsed / 1000.0f;
}