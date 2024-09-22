#include "../include/Sprite.h"

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

Sprite::Data Sprite::Data::None = Sprite::Data(nullptr, Vector3(), Vector3());

// Sprite Data Constructor
Sprite::Data::Data(
	const CHAR_INFO*** const spriteSheet,
	const Vector3 spriteSize,
	const Vector3 spriteAnchorPoint
) :
	sheet(spriteSheet),
	size(spriteSize),
	anchorPoint(spriteAnchorPoint)
{ }

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Sprite Allocator
Sprite* Sprite::Allocate()
{
	return new Sprite();
}

// Sprite Constructor
Sprite::Sprite() :
	sheet(nullptr),
	size(Vector3::Zero),
	anchorPoint(Vector3::Zero),
	m_isValid(false)
{ }

// Sprite Destructor
Sprite::~Sprite()
{
	Release();
}

// Check if is Initialized & Valid
bool Sprite::isValid() const
{
	return m_isValid;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Initialize Data
void Sprite::Init(const Sprite::Data spriteData)
{
	Init(spriteData.sheet, spriteData.size, spriteData.anchorPoint);
}

// Initialize Data
void Sprite::Init(const CHAR_INFO*** spriteSheet, Vector3 spriteSize, Vector3 spriteAnchorPoint)
{
	// Release if already Valid
	if (isValid()) {
		Release();
	}
	
	// Assign Data
	sheet = spriteSheet;
	size = spriteSize;
	anchorPoint = spriteAnchorPoint;

	// Set Valid flag
	m_isValid = true;
}

// Release Data & Settings
void Sprite::Release()
{
	// Release Data
	sheet = nullptr;
	size = Vector3::Zero;
	anchorPoint = Vector3::Zero;

	// Set Invalid flag
	m_isValid = false;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Get Sprite Size (Readonly)
const Vector3& Sprite::getSize() const
{
	return size;
}

// Get Anchor Point (Readonly)
const Vector3& Sprite::getAnchorPoint() const
{
	return anchorPoint;
}

// Get Sprite Sheet (Readonly)
const CHAR_INFO*** const Sprite::getSheet() const
{
	return sheet;
}

void Sprite::setSheet(const CHAR_INFO*** spriteSheet, Vector3 spriteSize, Vector3 spriteAnchorPoint)
{
	sheet = spriteSheet;
	size = spriteSize;
	anchorPoint = spriteAnchorPoint;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Flip Vertical Sprite
void Sprite::setFlipVertical(bool flip)
{
	flipVertical = flip;
}

// Flip Horizontal Sprite
void Sprite::setFlipHorizontal(bool flip)
{
	flipHorizontal = flip;
}

bool Sprite::isFlipVertical() const
{
	return flipVertical;
}

bool Sprite::isFlipHorizontal() const
{
	return flipHorizontal;
}