#include "../include/SpriteDestroyer.h"

SpriteDestroyer::SpriteDestroyer(const SpriteHelper::ParseData spriteData) :
	spriteSheet(spriteData.spriteSheet),
	xSize((unsigned int)spriteData.spriteSize.x),
	ySize((unsigned int)spriteData.spriteSize.y)
{ }

SpriteDestroyer::SpriteDestroyer(const Sprite::Data spriteData) :
	spriteSheet(spriteData.sheet),
	xSize((unsigned int)spriteData.size.x),
	ySize((unsigned int)spriteData.size.y)
{ }

SpriteDestroyer::SpriteDestroyer(
	const CHAR_INFO*** const sheet,
	const Vector3 size
) :
	spriteSheet(sheet),
	xSize((unsigned int)size.x),
	ySize((unsigned int)size.y)
{ }

SpriteDestroyer::~SpriteDestroyer()
{
	SpriteHelper::release(spriteSheet, ySize, xSize);
}