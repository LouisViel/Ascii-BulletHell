#include "../include/GameLoader.h"
#include "../include/Random.h"
#include "../include/SpriteHelper.h"
#include "../include/SpriteDestroyer.h"
#include "../include/ArrayDestroyer.h"
#include "../include/Player.h"
#include "../include/BulletSpawner.h"

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void GameLoader::Load(GameObjectManager* const gameObjectManager)
{
	LoadPlayer(gameObjectManager);
	LoadBulletSpawners(gameObjectManager);
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void GameLoader::LoadPlayer(GameObjectManager* const gameObjectManager)
{
	// Player Settings
	const double playerSpeed = 1.0;
	const double playerShiedDuration = 1;
	const unsigned int playerLife = 3;
	std::string spriteSheets[playerLife] = {
		" -0|#-15| -0\n#-15|@-10|#-15\n -0|#-15| -0", // FULL Life
		" -0|#-15| -0\n#-15|@-6|#-15\n -0|#-15| -0", // MID Life
		" -0|#-15| -0\n#-15|@-12|#-15\n -0|#-15| -0" // LOW Life
	};

	// Allocate Player Sprite Sheets
	Sprite::Data** spriteDatas = new Sprite::Data*[playerLife];
	for (int iSpriteSheet{ 0 }; iSpriteSheet < playerLife; ++iSpriteSheet) {
		const SpriteHelper::ParseData parseData = SpriteHelper::parse(spriteSheets[iSpriteSheet]);
		spriteDatas[iSpriteSheet] = new Sprite::Data(parseData.spriteSheet, parseData.spriteSize, Vector3::Zero );
	}

	// Player Components Setup
	Component<GameObject>** const components = new Component<GameObject>*[1] { new Player(
		playerSpeed, playerShiedDuration, playerLife,
		(const Sprite::Data** const)spriteDatas
	) };

	// Player Injection into Game
	gameObjectManager->initializeObject(Vector3(0, 0, 4), *spriteDatas[0], components, 1);
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void GameLoader::LoadBulletSpawners(GameObjectManager* const gameObjectManager)
{
	constexpr int spawnerCount = 8;

	constexpr int COLOR_Blue = 16 + 1;
	constexpr int COLOR_Green = 32 + 2;
	constexpr int COLOR_Cyan = 48 + 3;
	constexpr int COLOR_Red = 64 + 4;
	constexpr int COLOR_Pink = 80 + 5;
	constexpr int COLOR_Yellow = 96 + 6;
	constexpr int COLOR_Grey = 128 + 8;
	

	// Spawn Settings
	const Vector3 spawnDelay = Vector3(0.75, 2);
	const Vector3 sizeRange = Vector3(2, 6);
	const Vector3 speedRange = Vector3(2.35, 3.75);

	// Sprite Pool Settings
	const unsigned int characterPoolSize = 3;
	const char* const characterPool = new char[characterPoolSize] { 'o', 'x', '#' };
	const unsigned int attributePoolSize = 7;
	const int* const attributePool = new int[attributePoolSize] { COLOR_Blue, COLOR_Green, COLOR_Cyan, COLOR_Red, COLOR_Pink, COLOR_Yellow, COLOR_Grey };
	const bool autoReleasePool = false;

	// Instantiate Bullet Spawners
	for (int iSpawner{ 0 }; iSpawner < spawnerCount; ++iSpawner) {
		Component<GameObject>** const components = new Component<GameObject>*[1] { new BulletSpawner(
			gameObjectManager, spawnDelay, sizeRange, speedRange,
			characterPool, characterPoolSize,
			attributePool, attributePoolSize,
			autoReleasePool
		) };
		gameObjectManager->initializeObject(Vector3::Zero, Sprite::Data::None, components, 1);
	}

	// Create an object to automatically release Sprite Pools Memory
	Component<GameObject>** const components = new Component<GameObject>*[2] { new ArrayDestroyer(characterPool), new ArrayDestroyer(attributePool) };
	gameObjectManager->initializeObject(Vector3::Zero, Sprite::Data::None, components, 2);
}