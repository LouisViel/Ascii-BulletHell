#pragma once
#include <Windows.h>
#include "GameSettings.h"
#include "Clock.h"
#include "InputHandler.h"
#include "CharInfoHandler.h"
#include "GameObjectManager.h"

class Game
{
public:
	// Constructor Instructions
	Game& operator = (const Game& other) = delete;
	Game(const Game& other) = delete;
	Game();
	~Game();

	/**
	 * @brief Update Game
	 */
	void update();

	/**
	 * @brief Allow Managing Resize of Console.
	 */
	void checkResize();

	/**
	 * @brief Render Game to Console.
	 */
	void render();

	/**
	 * @brief Post Render Game.
	 */
	void postRender();

private:
	// Constant Settings
	COORD dwBufferSize = { GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT };
	SMALL_RECT rcRegion = { 0, 0, GameSettings::SCREEN_WIDTH - 1, GameSettings::SCREEN_HEIGHT - 1 };
	COORD dwBufferCoord = { 0, 0 };

	// Runtime Constants
	HANDLE hOutput;
	CONSOLE_SCREEN_BUFFER_INFO* csbiInfo;
	RenderData** renderDataBuffer;
	CHAR_INFO* renderBuffer;

	// Runtime Managers
	Clock* clock;
	InputHandler* inputHandler;
	CharInfoHandler* charInfoHandler;
	GameObjectManager* gameObjectManager;
};