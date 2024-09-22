#include "../include/Bullet.h"
#include "../include/Clock.h"
#include "../include/GameSettings.h"
#include "../include/GameObjectManager.h"

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

Bullet::Bullet(
	const Vector3 movement,
	const double speed
) :
	deltaTime(Clock::getDeltaTime()),
	bulletMovement(movement),
	bulletSpeed(speed)
{ }

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void Bullet::Update(GameObject* const target)
{
	// The number of pixel to move every seconds;
	constexpr double MOVE = 15.0;

	// The number of pixel to move this frame
	double frameMovement = MOVE * deltaTime;
	double moveX = frameMovement * bulletMovement.x,
		moveY = frameMovement * bulletMovement.y;

	// Apply Movement to Bullet
	Vector3& position = target->position;
	position += Vector3(moveX, moveY);

	// Compute Bullet Movement Bounds
	const double widthMaxBounds = (double)GameSettings::currentScreenWidth;
	const double heightMaxBounds = (double)GameSettings::currentScreenHeight;
	const double widthMinBounds = 0.0, heightMinBounds = 0.0;

	// Release Bullet if out of Bounds
	if (position.x < widthMinBounds || position.x > widthMaxBounds ||
		position.y < heightMinBounds || position.y > heightMaxBounds) {
		GameObjectManager::getSingleton()->releaseObject(target->getId());
	}
}