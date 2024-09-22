#pragma once
#include "GameObject.h"
#include "SpriteHelper.h"

class SpriteDestroyer final : public Component<GameObject>
{
public:
	SpriteDestroyer(const SpriteHelper::ParseData spriteData);
	SpriteDestroyer(const Sprite::Data spriteData);
	SpriteDestroyer(const CHAR_INFO*** const spriteSheet, const Vector3 spriteSize);
	~SpriteDestroyer();
	void Update(GameObject* const target) override {}
private:
	const CHAR_INFO*** const spriteSheet;
	const unsigned int xSize, ySize;
};