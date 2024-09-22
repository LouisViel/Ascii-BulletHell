// Include Min/Max Functions
#define NOMINMAX
#include <algorithm>

// Include Instructions
#include "../include/Player.h"
#include "../include/GameSettings.h"
#include "../include/Clock.h"
#include "../include/SpriteHelper.h"

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

Player::Player(const double playerSpeed, const double shieldDuration, const int playerLife, const Sprite::Data** const spriteDatas) :
	deltaTime(Clock::getDeltaTime()),
	inputKey(InputHandler::getCurrentKey()),
	m_spriteDatas(spriteDatas),
	m_shieldDuration(shieldDuration),
	currentShield(shieldDuration + 1.5),
	m_playerLife(playerLife),
	currentLife(playerLife),
	speed(playerSpeed)
{ }

Player::~Player()
{
	// Release Sprite Datas Memory
	for (int iSpriteData{ 0 }; iSpriteData < m_playerLife; ++iSpriteData) {
		const Sprite::Data* const spriteData = m_spriteDatas[iSpriteData];
		SpriteHelper::release(spriteData->sheet, spriteData->size);
		delete spriteData;
	}
	delete[] m_spriteDatas;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void Player::setSpeed(double speed)
{
	this->speed = speed;
}

double Player::getSpeed() const
{
	return speed;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void Player::Update(GameObject* const target)
{
	// If shield active, process it
	if (currentShield > 0) {
		currentShield -= deltaTime;
	}

	constexpr double MOVE = 25.0; // The number of pixel to move every seconds;
	double moveX = 0, moveY = 0; // The number of pixel to move this frame

	// Compute Frame Movement
	switch (inputKey) {
		case InputHandler::InputKey::Up:
			moveY = -MOVE * speed * deltaTime;
			break;
		case InputHandler::InputKey::Right:
			moveX = MOVE * speed * deltaTime;
			break;
		case InputHandler::InputKey::Down:
			moveY = MOVE * speed * deltaTime;
			break;
		case InputHandler::InputKey::Left:
			moveX = -MOVE * speed * deltaTime;
			break;
	}
	
	// Apply Movement to Player
	Vector3& position = target->position;
	position += Vector3(moveX, moveY);

	// Get Sprite Settings
	const Sprite* const sprite = target->getSprite();
	const Vector3 spriteSize = sprite->getSize();
	const Vector3 spriteAnchorPoint = sprite->getAnchorPoint();

	// Compute Player Movement Bounds
	const double widthMaxBounds = (double)GameSettings::currentScreenWidth - spriteSize.x;
	const double heightMaxBounds = (double)GameSettings::currentScreenHeight - spriteSize.y;
	const double widthMinBounds = spriteAnchorPoint.x, heightMinBounds = spriteAnchorPoint.y;

	// Update player collision with "camera" borders
	position.x = std::max(std::min(position.x, widthMaxBounds), widthMinBounds);
	position.y = std::max(std::min(position.y, heightMaxBounds), heightMinBounds);
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void Player::PostRender(GameObject* const target, RenderData** const renderDataBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize)
{
	// Do not check for collision if shield is active
	if (currentShield > 0) { return; }

	// Get Object Settings
	Sprite* const sprite = target->getSprite();
	const CHAR_INFO*** const sheet = sprite->getSheet();
	const Vector3& anchorPoint = sprite->getAnchorPoint();
	const Vector3& spriteSize = sprite->getSize();
	const Vector3& position = target->position;

	// Setup Position + Z Index + Pos Limits
	int zIndex = (int)std::ceil(position.z);
	int xPosition = (int)std::round(position.x - anchorPoint.x);
	int yPosition = (int)std::round(position.y - anchorPoint.y);
	int xPosLimit = xPosition + (int)spriteSize.x;
	int yPosLimit = yPosition + (int)spriteSize.y;

	// Clean Positions & Limits
	unsigned int xNicePosLimit = std::max(xPosLimit, 0);
	unsigned int yNicePosLimit = std::max(yPosLimit, 0);
	unsigned int xNicePosition = std::max(xPosition, 0);
	unsigned int yNicePosition = std::max(yPosition, 0);

	// Loop and Check Vertical (Y) Collision
	for (unsigned int jSprite{ 0 }, yPos{ yNicePosition };
		yPos < yNicePosLimit && yPos < yBufferSize;
		++jSprite, ++yPos
	) {

		// Loop and Check Horizontal (X) Collision
		for (unsigned int iSprite{ 0 }, xPos{ xNicePosition };
			xPos < xNicePosLimit && xPos < xBufferSize;
			++iSprite, ++xPos
		) {

			// Compare Render Data to check if there is a collision with something
			const CHAR_INFO* const charInfo = sheet[jSprite][iSprite];
			if (charInfo->Char.UnicodeChar != ' ') {
				const RenderData& renderData = renderDataBuffer[yPos][xPos];
				const CHAR_INFO* const renderDataCharInfo = renderData.charInfo;
				if (
					renderDataCharInfo->Attributes != charInfo->Attributes &&
					renderDataCharInfo->Char.UnicodeChar != charInfo->Char.UnicodeChar
				) {

					// Take damage and Exit, nothing more to do
					takeDamage(sprite);
					return;

				}
			}

		}

	}
}

inline void Player::takeDamage(Sprite* const sprite)
{
	// Reset Shield, Take Damage, And Switch Player Sprite or Stop the game
	currentShield = m_shieldDuration;
	if (--currentLife > 0) {
		const Sprite::Data* spriteData = m_spriteDatas[m_playerLife - currentLife];
		sprite->setSheet(spriteData->sheet, spriteData->size, spriteData->anchorPoint);
	} else { GameSettings::running = false; }
}