#pragma once
#include "GameObjectManager.h"

class BulletSpawner final : public Component<GameObject>
{
public:
	// Constructor Instructions
	~BulletSpawner();
	BulletSpawner(
		GameObjectManager* const objectManager,
		const Vector3 delayRange,
		const Vector3 sizeRange,
		const Vector3 speedRange,
		const char* const characterPool,
		const unsigned int characterPoolSize,
		const int* const attributePool,
		const unsigned int attributePoolSize,
		const bool autoReleasePool
	);

	// Update Bullet Spawn
	void Update(GameObject* const target) override;

private:
	// Spawner Settigns
	GameObjectManager* const gameObjectManager;
	const float& deltaTime;
	double currentDelay;

	// Spawn Settings
	const Vector3 spawnDelayRange;
	const Vector3 spawnSizeRange;
	const Vector3 spawnSpeedRange;

	// Spawn Sprite Pools
	const bool m_autoReleasePool;
	const char* const m_characterPool;
	const unsigned int m_characterPoolSize;
	const int* const m_attributePool;
	const unsigned int m_attributePoolSize;

	// Spawn Bullet
	void spawnBullet();
};