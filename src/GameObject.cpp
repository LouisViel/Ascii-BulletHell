#include "../include/GameObject.h"

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// GameObject Allocator 
GameObject* GameObject::Allocate()
{
	return new GameObject();
}

// GameObject Constructor
GameObject::GameObject() :
	position(Vector3::Zero),
	sprite(Sprite::Allocate()),
	components(nullptr),
	componentsCount(NULL),
	m_isValid(false),
	m_objectId(NULL)
{ }

// GameObject Destructor
GameObject::~GameObject()
{
	Release();
	delete sprite;
}

// Check if is Initialized & Valid
bool GameObject::isValid() const
{
	return m_isValid;
}

// Get Allocation Object Id
const unsigned int GameObject::getId() const
{
	return m_objectId;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

bool GameObject::operator ==(const GameObject& other) const
{
	return m_objectId == other.m_objectId && position == other.position;
}

bool GameObject::operator ==(const unsigned int id) const
{
	return m_objectId == id;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Initialize Data
void GameObject::Init(Vector3 objPosition, const Sprite::Data spriteData, Component<GameObject>** const objComponents, const unsigned int objComponentsCount)
{
	// Release if already Valid
	if (isValid()) {
		Release();
	}

	// Assign Data
	position = objPosition;
	components = objComponents;
	componentsCount = objComponentsCount;

	// Initialize Members
	sprite->Init(spriteData);

	// Set Valid flag
	static unsigned int uniqueIdHandle = 0;
	m_objectId = ++uniqueIdHandle;
	m_isValid = true;
}

// Release Data & Settings
void GameObject::Release()
{
	// Release Components Individually
	for (unsigned int iComponent{ 0 }; iComponent < componentsCount; ++iComponent) {
		delete components[iComponent];
	}

	// Release Component Array
	if (components != nullptr) {
		delete [] components;
		components = nullptr;
	}

	// Release Data
	position = Vector3::Zero;
	componentsCount = 0;

	// Release Members
	sprite->Release();

	// Set Invalid flag
	m_objectId = NULL;
	m_isValid = false;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Get Sprite Pointer
Sprite* const GameObject::getSprite() const
{
	return sprite;
}

// Get Components Array Pointer
Component<GameObject>** const GameObject::getComponents() const
{
	return components;
}

// Get Components Count
const unsigned int GameObject::getComponentsCount() const
{
	return componentsCount;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Update GameObject
void GameObject::update()
{
	// Update Components
	for (unsigned int iComponent{ 0 }; iComponent < componentsCount; ++iComponent) {
		components[iComponent]->Update(this);
	}
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Post Render GameObject
void GameObject::postRender(RenderData** const renderBuffer, const unsigned int xBufferSize, const unsigned int yBufferSize)
{
	// Post Render Components
	for (unsigned int iComponent{ 0 }; iComponent < componentsCount; ++iComponent) {
		components[iComponent]->PostRender(this, renderBuffer, xBufferSize, yBufferSize);
	}
}