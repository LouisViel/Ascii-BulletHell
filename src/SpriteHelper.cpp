#include "../include/SpriteHelper.h"
#include "../include/CharInfoHandler.h"

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

SpriteHelper::ParseData::ParseData(
	const CHAR_INFO*** const sheet,
	const Vector3 size
) :
	spriteSheet(sheet),
	spriteSize(size)
{ }

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

const SpriteHelper::ParseData SpriteHelper::parse(const std::string input)
{
	std::istringstream inputStream(input);
	return SpriteHelper::parse(inputStream);
}

const SpriteHelper::ParseData SpriteHelper::parse(std::istream& inputStream)
{
	// Get CharInfoHandler + Bad CharInfo
	CharInfoHandler* const charInfoHandler = CharInfoHandler::getSingleton();
	const CHAR_INFO* const badCharInfo = charInfoHandler->getBadCharInfo();

	// Setup Parse Settings
	std::vector<CharInfoBuffer*> sheetBuffer = std::vector<CharInfoBuffer*>();
	unsigned int sheetSize{ 0 }, lineSize{ 0 }, currentLineSize{ 0 };
	WORD attribute;

	// Loop over input Stream lines
	std::string lineData, charInfoData, charData;
	while (std::getline(inputStream, lineData, lineSplitter)) {

		// Loop over charInfo datas from lines
		CharInfoBuffer* const lineBuffer = new CharInfoBuffer();
		std::istringstream lineStream(lineData);
		while (std::getline(lineStream, charInfoData, charSplitter)) {

			// Read + Cast charInfo datas into CharInfo
			const CHAR_INFO* charInfo = badCharInfo;
			std::istringstream charStream(charInfoData);
			if (std::getline(charStream, charData, dataSplitter)) {

				// Read Attribute + Get mapped CharInfo
				charStream >> attribute;
				if (!charStream.fail()) {
					charInfo = charInfoHandler->getCharInfo(
						*charData.c_str(),
						attribute
					);
				}
			}

			// Save CharInfo into Line Buffer
			lineBuffer->push_back(charInfo);
		}

		// Save Line Buffer into Sheet Buffer
		sheetBuffer.push_back(lineBuffer);

		// Update Sheet Dimensions
		++sheetSize;
		currentLineSize = (unsigned int)lineBuffer->size();
		if (currentLineSize > lineSize) {
			lineSize = currentLineSize;
		}
	}

	// Loop over SheetBuffer and Copy them into spriteSheet
	const CHAR_INFO*** const spriteSheet = new const CHAR_INFO**[sheetSize];
	for (unsigned int iSheet{ 0 }; iSheet < sheetSize; ++iSheet) {
		CharInfoBuffer* const lineBuffer = sheetBuffer[iSheet];
		const CHAR_INFO** const spriteLine = new const CHAR_INFO*[lineSize];

		// Resize Line if parsed data was incoherent
		if (lineBuffer->size() < lineSize) {
			lineBuffer->resize(lineSize, badCharInfo);
		}

		// Copy LineBuffer into SpriteLine
		std::copy(lineBuffer->begin(), lineBuffer->end(), spriteLine);
		spriteSheet[iSheet] = spriteLine;
		delete lineBuffer;
	}

	// Return Result Parsed Data
	return ParseData(spriteSheet, Vector3(lineSize, sheetSize));
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Release Parsed Data Memory Allocation
void SpriteHelper::release(ParseData parseData)
{
	SpriteHelper::release(parseData.spriteSheet, (unsigned int)parseData.spriteSize.x, (unsigned int)parseData.spriteSize.y);
}

// Release Parsed Data Memory Allocation
void SpriteHelper::release(const CHAR_INFO*** const spriteSheet, const Vector3 spriteSize)
{
	SpriteHelper::release(spriteSheet, (unsigned int)spriteSize.x, (unsigned int)spriteSize.y);
}

// Release Parsed Data Memory Allocation
void SpriteHelper::release(const CHAR_INFO*** const spriteSheet, const unsigned int sheetSize, const unsigned int lineSize)
{
	// Get CharInfoHandler
	CharInfoHandler* const charInfoHandler = CharInfoHandler::getSingleton();

	// Loop over Sheet Lines and release them
	for (unsigned int iSheet{ 0 }; iSheet < sheetSize; ++iSheet) {
		const CHAR_INFO** const spriteLine = spriteSheet[iSheet];

		// Loop over Line CharInfos and release them
		for (unsigned int iLine{ 0 }; iLine < lineSize; ++iLine) {
			charInfoHandler->releaseCharInfo(spriteLine[iLine]);
		}

		// Release Sprite Line Array
		delete[] spriteLine;
	}

	// Release Sprite Sheet Array
	delete[] spriteSheet;
}