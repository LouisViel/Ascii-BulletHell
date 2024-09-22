// Include Min/Max Functions
#define NOMINMAX
#include <algorithm>

// Include Instructions
#include "../include/GameObjectManager.h"
#include <stdexcept>
#include <string>
#include <cmath>

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

GameObjectManager* GameObjectManager::singleton = nullptr;

GameObjectManager* const GameObjectManager::getSingleton()
{
	return singleton;
}

GameObjectManager::GameObjectManager()
{
	// Initialize GameObjects Pool
	gameObjects = new std::vector<GameObject*>(gameObjectBufferSize, nullptr);
	for (unsigned int iObject{ 0 }; iObject < gameObjectBufferSize; ++iObject) {
		gameObjects->operator[](iObject) = GameObject::Allocate();
	}
	singleton = this;
}

GameObjectManager::~GameObjectManager()
{
	// Clear + Release GameObjects Pool
	for (int iObject{ 0 }; iObject < (int)gameObjects->size(); ++iObject) {
		GameObject* gameObject = gameObjects->operator[](iObject);
		gameObjects->operator[](iObject) = nullptr;
		delete gameObject;
	}
	delete gameObjects;
	singleton = nullptr;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

const unsigned int GameObjectManager::initializeObject(const Vector3 position, const Sprite::Data spriteData, Component<GameObject>** const components, const unsigned int componentsCount)
{
	// Try Initialize GameObject from Pool
	for (int iObject{ 0 }; iObject < (int)gameObjects->size(); ++iObject) {
		GameObject* gameObject = gameObjects->operator[](iObject);
		if (!gameObject->isValid()) {
			gameObject->Init(position, spriteData, components, componentsCount);
			return gameObject->getId();
		}
	}

	// If Pool was full, Create new GameObject
	GameObject* gameObject = GameObject::Allocate();
	gameObject->Init(position, spriteData, components, componentsCount);
	gameObjects->push_back(gameObject);
	return gameObject->getId();
}

void GameObjectManager::releaseObject(const unsigned int id)
{
	// If target not initialized, do nothing
	if (id == 0) { return; }

	// Try Found and Release Target
	for (int iObject{ 0 }; iObject < (int)gameObjects->size(); ++iObject) {
		GameObject* gameObject = gameObjects->operator[](iObject);
		if (gameObject->operator==(id)) {
			gameObject->Release();
			return;
		}
	}

	// If no target founded, throw an error cause this should not happen
	std::string exception = "No GameObject with id (" + std::to_string(id) + ") was found for Release";
	throw std::invalid_argument(exception);
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void GameObjectManager::updateObjects()
{
	// Loop over GameObjects & Update them
	for (int iObject{ 0 }; iObject < (int)gameObjects->size(); ++iObject) {
		GameObject* gameObject = gameObjects->operator[](iObject);
		if (gameObject->isValid()) {
			gameObject->update();
		}
	}
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void GameObjectManager::renderObjects(RenderData** const renderBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize)
{
	// Loop over GameObjects & Render them if Valid
	for (GameObject* gameObject : *gameObjects) {
		if (gameObject->isValid()) {
			renderObject(gameObject, renderBuffer, xBufferSize, yBufferSize);
		}
	}
}

inline void GameObjectManager::renderObject(const GameObject* const gameObject, RenderData** const renderBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize)
{
	// Get GameObject Datas & Settings
	const Sprite* const sprite = gameObject->getSprite();
	const CHAR_INFO*** const sheet = sprite->getSheet();
	const Vector3& anchorPoint = sprite->getAnchorPoint();
	const Vector3& spriteSize = sprite->getSize();
	const Vector3& position = gameObject->position;

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

	// Loop and Write Vertical (Y) Sprite Sheet
	for (unsigned int jSprite{ 0 }, yPos{ yNicePosition };
		yPos < yNicePosLimit && yPos < yBufferSize;
		++jSprite, ++yPos
	) {

		// Loop and Write Horizontal (X) Sprite Sheet
		for (unsigned int iSprite{ 0 }, xPos{ xNicePosition };
			xPos < xNicePosLimit && xPos < xBufferSize;
			++iSprite, ++xPos
		) {

			// Compare Z Index and Write Data if good
			RenderData& renderData = renderBuffer[yPos][xPos];
			if (zIndex >= renderData.zIndex) {
				const CHAR_INFO * const charInfo = sheet[jSprite][iSprite];
				if (charInfo->Char.UnicodeChar != ' ') {
					renderData.charInfo = charInfo;
					renderData.zIndex = zIndex;
				}
			}

		}
	}
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void GameObjectManager::postRenderObjects(RenderData** const renderBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize)
{
	// Loop over GameObjects & Post Render them if Valid
	for (int iObject{ 0 }; iObject < (int)gameObjects->size(); ++iObject) {
		GameObject* gameObject = gameObjects->operator[](iObject);
		if (gameObject->isValid()) {
			gameObject->postRender(renderBuffer, xBufferSize, yBufferSize);
		}
	}
}