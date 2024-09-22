#include "../include/BulletSpawner.h"
#include "../include/Random.h"
#include "../include/Clock.h"
#include "../include/GameSettings.h"
#include "../include/SpriteHelper.h"
#include "../include/SpriteDestroyer.h"
#include "../include/Bullet.h"
#include <string>
#include <cmath>

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

BulletSpawner::BulletSpawner(
	GameObjectManager* const objectManager,
	const Vector3 delayRange,
	const Vector3 sizeRange,
	const Vector3 speedRange,
	const char* const characterPool,
	const unsigned int characterPoolSize,
	const int* const attributePool,
	const unsigned int attributePoolSize,
	const bool autoReleasePool
) :
	deltaTime(Clock::getDeltaTime()),
	gameObjectManager(objectManager),
	spawnDelayRange(delayRange),
	spawnSizeRange(sizeRange),
	spawnSpeedRange(speedRange),
	m_characterPool(characterPool),
	m_characterPoolSize(characterPoolSize),
	m_attributePool(attributePool),
	m_attributePoolSize(attributePoolSize),
	m_autoReleasePool(autoReleasePool)
{
	spawnBullet();
}

BulletSpawner::~BulletSpawner()
{
	if (m_autoReleasePool) {
		delete[] m_characterPool;
		delete[] m_attributePool;
	}
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void BulletSpawner::Update(GameObject* const target)
{
	// Update Delay + Spawn if reached
	currentDelay -= (double)deltaTime;
	if (currentDelay <= 0.0f) {
		spawnBullet();
	}
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void BulletSpawner::spawnBullet()
{
	// Re-Initialize Spawn Delay
	currentDelay = Random::range(spawnDelayRange.x, spawnDelayRange.y);

	// Constexpr Declaration for Mouvement Random
	constexpr double MovementMin = 0.3;
	constexpr double MovementMax = 0.6;

	// Generate Spawn Position + Movement
	Vector3 movement, position = Vector3(0, 0, 5);
	switch (Random::range(1, 4)) {
		case 1: // Camera Top Side
			position.y = 0.0;
			position.x = Random::range(0.0, (double)GameSettings::currentScreenWidth);
			movement = Vector3(Random::range(-MovementMin, MovementMin), Random::range(MovementMin, MovementMax));
			break;
		case 2: // Camera Left Side
			position.y = Random::range(0.0, (double)GameSettings::currentScreenHeight);
			position.x = 0.0;
			movement = Vector3(Random::range(MovementMin, MovementMax), Random::range(-MovementMin, MovementMin));
			break;
		case 3: // Camera Bottom Side
			position.y = (double)GameSettings::currentScreenHeight;
			position.x = Random::range(0.0, (double)GameSettings::currentScreenWidth);
			movement = Vector3(Random::range(-MovementMin, MovementMin), Random::range(-MovementMax, -MovementMin));
			break;
		case 4: // Camera Right Side
			position.y = Random::range(0.0, (double)GameSettings::currentScreenHeight);
			position.x = (double)GameSettings::currentScreenWidth;
			movement = Vector3(Random::range(-MovementMax, -MovementMin), Random::range(-MovementMin, MovementMin));
			break;
	}
	
	// Generate Sprite Settings
	const char character = m_characterPool[Random::range(0, m_characterPoolSize - 1)];
	const int attribute = m_attributePool[Random::range(0, m_attributePoolSize - 1)];

	// Compute Sprite Sheet
	std::stringstream spriteStream{};
	Vector3 size = Vector3(Random::range(spawnSizeRange.x, spawnSizeRange.y), Random::range(spawnSizeRange.x, spawnSizeRange.y));
	for (int iSheet{ 0 }; iSheet < size.y; ++iSheet, spriteStream << SpriteHelper::lineSplitter) {
		for (int iLine{ 0 }; iLine < size.x; ++iLine, spriteStream << SpriteHelper::charSplitter) {
			spriteStream << character << SpriteHelper::dataSplitter << std::to_string(attribute);
		}
	}

	// Compute Sprite Data
	spriteStream.seekg(0).clear();
	const SpriteHelper::ParseData parseData = SpriteHelper::parse(spriteStream);
	const Vector3 anchorPoint = Vector3(std::floor(parseData.spriteSize.x / 2), std::floor(parseData.spriteSize.y / 2));
	const Sprite::Data spriteData = Sprite::Data(parseData.spriteSheet, parseData.spriteSize, anchorPoint);
	
	// Compute Components + Initialize Bullet
	const double speed = Random::range(spawnSpeedRange.x, spawnSpeedRange.y);
	Component<GameObject>** const components = new Component<GameObject>*[2] { new Bullet(movement, speed), new SpriteDestroyer(parseData) };
	gameObjectManager->initializeObject(position, spriteData, components, 2);
}