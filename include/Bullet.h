#pragma once
#include "GameObject.h"

class Bullet final : public Component<GameObject>
{
public:
	Bullet(const Vector3 movement, const double speed);
	void Update(GameObject* const target) override;

private:
	const float& deltaTime;
	const Vector3 bulletMovement;
	const double bulletSpeed;
};