#pragma once
#include <map>
#include <iterator>
#include <Windows.h>
#include "RenderData.h"

class CharInfoHandler
{
public:
	// Singleton
	static CharInfoHandler* const getSingleton();

	// Constructor Instructions
	CharInfoHandler& operator = (const CharInfoHandler& other) = delete;
	CharInfoHandler(const CharInfoHandler& other) = delete;
	CharInfoHandler();
	~CharInfoHandler();

	// Member Getters
	const CHAR_INFO* const getBadCharInfo() const;
	const CHAR_INFO* const getDefaultCharInfo() const;
	const RenderData* const getDefaultRenderData() const;

	// Public Methods
	const CHAR_INFO* const getCharInfo(WCHAR character, const WORD attributes);
	void releaseCharInfo(const CHAR_INFO* const charInfo);

private:
	struct CharInfoWrapper
	{
	public:
		// Wrapper Members
		unsigned int referenceCount = 1;
		const CHAR_INFO* const charInfo;

		// Contructor Instructions
		~CharInfoWrapper();
		CharInfoWrapper(const CHAR_INFO* const charInfo);
		CharInfoWrapper& operator = (CharInfoWrapper& other) = delete;
		CharInfoWrapper(const CharInfoWrapper& other) = delete;
	};

	// Declare typename alias
	using CharInfoIterator = std::multimap<WCHAR, CharInfoWrapper*>::iterator;

	// Singleton
	static CharInfoHandler* singleton;

	// Constant Members
	CHAR_INFO* const badCharInfo;
	CHAR_INFO* const defaultCharInfo;
	RenderData* const defaultRenderData;
	std::multimap<WCHAR, CharInfoWrapper*>* charInfos;

	// Private Methods
	inline const CHAR_INFO* const createCharInfo(WCHAR character, const WORD attributes);
	inline bool compare(const CHAR_INFO* const first, const CHAR_INFO* const second);
	inline bool compare(const CHAR_INFO* const first, WCHAR secondCharacter, const WORD secondAttributes);
};