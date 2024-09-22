#pragma once
#include <Windows.h>
#include "Vector3.h"

class Sprite
{
public:
	struct Data
	{
	public:
		static Data None;

		const CHAR_INFO*** const sheet;
		const Vector3 anchorPoint;
		const Vector3 size;
		Data(const CHAR_INFO*** const sheet, const Vector3 size, const Vector3 anchorPoint = Vector3::Zero);
	};

	// Sprite Allocation Methods
	static Sprite* Allocate();
	bool isValid() const;
	
	// Constructors Instructions
	Sprite& operator =(Sprite& other) = delete;
	Sprite(Sprite& other) = delete;
	~Sprite();

	// Init + Release Methods
	void Init(const Data spriteData);
	void Init(const CHAR_INFO*** spriteSheet, Vector3 spriteSize, Vector3 spriteAnchorPoint = Vector3::Zero);
	void Release();

	// Member Getters
	const Vector3& getSize() const;
	const Vector3& getAnchorPoint() const;
	const CHAR_INFO*** const getSheet() const;

	// Member Setters
	void setSheet(const CHAR_INFO*** spriteSheet, Vector3 spriteSize, Vector3 spriteAnchorPoint = Vector3::Zero);

	// Settings Setters/Getters
	void setFlipVertical(bool flip);
	void setFlipHorizontal(bool flip);
	bool isFlipVertical() const;
	bool isFlipHorizontal() const;

private:
	// Sprite Datas
	const CHAR_INFO*** sheet; // The sprite sheet (value readonly / pointer read-write)
	Vector3 anchorPoint; // The anchor point of the sprite
	Vector3 size; // The size of the sprite

	// Sprite Settings
	bool flipHorizontal = false; // Flip the sprite horizontally
	bool flipVertical = false; // Flip the sprite vertically

	// Allocation Utils
	bool m_isValid;
	Sprite();
};