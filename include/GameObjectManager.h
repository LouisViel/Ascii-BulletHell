#pragma once
#include <vector>
#include "GameObject.h"
#include "RenderData.h"

class GameObjectManager
{
public:
	// Singleton
	static GameObjectManager* const getSingleton();

	// Contructor Instructions
	GameObjectManager& operator = (GameObjectManager& other) = delete;
	GameObjectManager(const GameObjectManager& other) = delete;
	GameObjectManager();
	~GameObjectManager();

	// Object Management Methods
	const unsigned int initializeObject(const Vector3 position, const Sprite::Data spriteData, Component<GameObject>** const components, const unsigned int componentsCount);
	void releaseObject(const unsigned int id);

	// Object Update Methods
	void updateObjects();
	void renderObjects(RenderData** const renderBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize);
	void postRenderObjects(RenderData** const renderBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize);

private:
	// Singleton
	static GameObjectManager* singleton;

	// Private Members
	const unsigned int gameObjectBufferSize = 32;
	std::vector<GameObject*>* gameObjects;

	// Private Methods
	inline void renderObject(const GameObject* const gameObject, RenderData** const renderBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize);
};