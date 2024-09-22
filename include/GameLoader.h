#pragma once
#include "GameObjectManager.h"

class GameLoader
{
public:
	// Load Game
	static void Load(GameObjectManager* const gameObjectManager);

private:
	// Make class static
	GameLoader() = delete;
	~GameLoader() = delete;

	// Load Player
	static void LoadPlayer(GameObjectManager* const gameObjectManager);
	static void LoadBulletSpawners(GameObjectManager* const gameObjectManager);
};