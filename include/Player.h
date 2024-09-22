#pragma once
#include "InputHandler.h"
#include "GameObject.h"

class Player final : public Component<GameObject>
{
public:
	// Constructor Instructions
	~Player();
	Player(const double playerSpeed, const double m_shieldDuration, const int playerLife, const Sprite::Data** const spriteDatas);
	Player& operator =(Player& other) = delete;
	Player(const Player& other) = delete;
	Player() = delete;

	// Component Methods
	void Update(GameObject* const target) override;
	void PostRender(GameObject* const target, RenderData** const renderDataBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize) override;

	// Player Methods
	void setSpeed(double speed);
	double getSpeed() const;

private:
	// Player Utils References
	const InputHandler::InputKey& inputKey;
	const float& deltaTime;

	// Player Constants
	const int m_playerLife;
	const Sprite::Data** const m_spriteDatas;
	const double m_shieldDuration;

	// Player Members
	double currentShield;
	int currentLife;
	double speed;

	// Private Methods
	inline void takeDamage(Sprite* const sprite);
};