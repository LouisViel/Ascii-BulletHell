#pragma once

class GameSettings
{
public:
	static const unsigned int SCREEN_WIDTH = 312;
	static const unsigned int SCREEN_HEIGHT = 92;
	static unsigned int currentScreenWidth;
	static unsigned int currentScreenHeight;
	static bool running;
private:
	GameSettings() = delete;
	~GameSettings() = delete;
};