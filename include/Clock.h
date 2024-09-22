#pragma once
#include <windows.h>

class Clock
{
public:
	static const float& getDeltaTime();
	void updateDeltaTime();
	Clock();
	~Clock();

private:
	static Clock* singleton;
	float deltaTime;

	LARGE_INTEGER lastUpdateTime;
	LONGLONG freq;
};