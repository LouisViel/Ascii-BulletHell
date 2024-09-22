#pragma once
#include "Vector3.h"
#include "Sprite.h"
#include "Component.h"

class GameObject
{
public:
	// GameObject Allocation Methods
	static GameObject* Allocate();
	const unsigned int getId() const;
	bool isValid() const;

	// Constructors Instructions
	GameObject& operator =(GameObject& other) = delete;
	GameObject(GameObject& other) = delete;
	~GameObject();

	// Comparaisons Operators
	bool operator ==(const GameObject& other) const;
	bool operator ==(const unsigned int id) const;

	// Init + Release Methods
	void Init(Vector3 position, const Sprite::Data spriteData, Component<GameObject>** const components, const unsigned int componentsCount);
	void Release();

	// Public Members
	Vector3 position;

	// Member Getters
	Sprite* const getSprite() const;
	Component<GameObject>** const getComponents() const;
	const unsigned int getComponentsCount() const;

	// GameObject Methods
	void update();
	void postRender(RenderData** const renderBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize);

private:
	// GameObject Datas
	Sprite* sprite;
	Component<GameObject>** components;
	unsigned int componentsCount;

	// Allocation Utils
	bool m_isValid;
	unsigned int m_objectId;
	GameObject();
};