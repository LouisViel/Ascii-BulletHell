#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include "Vector3.h"

class SpriteHelper
{
public:
	struct ParseData
	{
		const CHAR_INFO*** const spriteSheet;
		const Vector3 spriteSize;
		ParseData(const CHAR_INFO*** const sheet, const Vector3 size);
	};

	// Helper Constants
	static const char lineSplitter = '\n';
	static const char charSplitter = '|';
	static const char dataSplitter = '-';

	// Parse Helper Methods
	static const ParseData parse(const std::string input);
	static const ParseData parse(std::istream& inputStream);

	// Release Helper Methods
	static void release(ParseData parseData);
	static void release(const CHAR_INFO*** const spriteSheet, const Vector3 spriteSize);
	static void release(const CHAR_INFO*** const spriteSheet, const unsigned int sheetSize, const unsigned int lineSize);

private:
	// Declare typename alias 
	using CharInfoBuffer = std::vector<const CHAR_INFO*>;

	// Make class static
	SpriteHelper() = delete;
	~SpriteHelper() = delete;
};