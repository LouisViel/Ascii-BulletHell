#pragma once
#include "GameObject.h"

class ArrayDestroyer final : public Component<GameObject>
{
public:
	ArrayDestroyer(const void* const arrayPointer);
	~ArrayDestroyer();
	void Update(GameObject* target) override { }

private:
	const void* const m_arrayPointer;
};