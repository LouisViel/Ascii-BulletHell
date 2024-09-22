#include "../include/CharInfoHandler.h"

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// CharInfoHandler Singleton
CharInfoHandler* CharInfoHandler::singleton = nullptr;

// Get CharInfoHandler Singleton
CharInfoHandler* const CharInfoHandler::getSingleton()
{
    return singleton;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// CharInfoWrapper Constructor
CharInfoHandler::CharInfoWrapper::CharInfoWrapper(const CHAR_INFO* const _charInfo) : charInfo(_charInfo)
{
    return;
}

// CharInfoWrapper Destructor
CharInfoHandler::CharInfoWrapper::~CharInfoWrapper()
{
    delete charInfo;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// CharInfoHandler Constructor
CharInfoHandler::CharInfoHandler() :
    badCharInfo(new CHAR_INFO()),
    defaultCharInfo(new CHAR_INFO()),
    defaultRenderData(new RenderData())
{
    // Allocate Bad Char Info
    badCharInfo->Char.UnicodeChar = '!';
    badCharInfo->Attributes = 1;

    // Allocate Default Char Info
    defaultCharInfo->Char.UnicodeChar = '.';
    defaultCharInfo->Attributes = 0;

    // Allocate Default Render Data
    defaultRenderData->charInfo = defaultCharInfo;
    defaultRenderData->zIndex = -1;

    // Create CharInfos multimap
    charInfos = new std::multimap<WCHAR, CharInfoWrapper*>();

    // Register Singleton
    singleton = this;
}

// CharInfoHandler Destructor
CharInfoHandler::~CharInfoHandler()
{
    // Release CharInfos multimap
    for (std::pair<WCHAR, CharInfoWrapper*> charInfo : *charInfos) {
        delete charInfo.second;
    }
    delete charInfos;

    // Release Default Render Data
    delete badCharInfo;
    delete defaultRenderData;
    delete defaultCharInfo;

    // Release singleton
    singleton = nullptr;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Get Bad CharInfo
const CHAR_INFO* const CharInfoHandler::getBadCharInfo() const
{
    return badCharInfo;
}

// Get Default CharInfo
const CHAR_INFO* const CharInfoHandler::getDefaultCharInfo() const
{
    return defaultCharInfo;
}

// Get Default Render Data
const RenderData* const CharInfoHandler::getDefaultRenderData() const
{
    return defaultRenderData;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Get a CharInfo for a Character + Attributes
const CHAR_INFO* const CharInfoHandler::getCharInfo(WCHAR character, const WORD attributes)
{
    // Return DefaultCharInfo/BadCharInfo if they are the target
    if (compare(defaultCharInfo, character, attributes)) { return defaultCharInfo; }
    if (compare(badCharInfo, character, attributes)) { return badCharInfo; }

    // Get all CharInfoWrapper mapped to character argument
    std::pair<CharInfoIterator, CharInfoIterator> charInfoIterators = charInfos->equal_range(character);
    CharInfoIterator it = charInfoIterators.first, end = charInfoIterators.second;

    // Loop over founded CharInfoWrapper
    while (it != end) {

        // Check if CharInfo Attributes matches
        CharInfoWrapper* const charInfoWrapper = it->second;
        const CHAR_INFO* const charInfo = charInfoWrapper->charInfo;
        if (charInfo->Attributes == attributes) {
            ++charInfoWrapper->referenceCount;
            return charInfo;
        }

        // Increment iterator
        ++it;
    }

    // If no CharInfo founded, Create one
    return createCharInfo(character, attributes);
}

// Create a new CharInfo in the Handler
inline const CHAR_INFO* const CharInfoHandler::createCharInfo(WCHAR character, const WORD attributes)
{
    CHAR_INFO* newCharInfo = new CHAR_INFO();
    newCharInfo->Char.UnicodeChar = character;
    newCharInfo->Attributes = attributes;
    charInfos->emplace(character, new CharInfoWrapper(newCharInfo));
    return newCharInfo;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Inform Handler we no longer use this CharInfo
void CharInfoHandler::releaseCharInfo(const CHAR_INFO* const charInfo)
{
    // If target is DefaultCharInfo/BadCharInfo, do nothing
    if (compare(defaultCharInfo, charInfo)) { return; }
    if (compare(badCharInfo, charInfo)) { return; }

    // Get Arguments
    const WCHAR character = charInfo->Char.UnicodeChar;
    const WORD attributes = charInfo->Attributes;

    // Get all CharInfoWrapper mapped to character argument
    
    std::pair<CharInfoIterator, CharInfoIterator> charInfoIterators = charInfos->equal_range(character);
    CharInfoIterator it = charInfoIterators.first, end = charInfoIterators.second;

    // Loop over founded CharInfoWrapper
    while (it != end) {

        // Check if CharInfo Attributes matches
        CharInfoWrapper* const charInfoWrapper = it->second;
        if (charInfoWrapper->charInfo->Attributes == attributes) {
            if (--charInfoWrapper->referenceCount == 0) {
                charInfos->erase(it);
                delete charInfoWrapper;
            }
            return;
        }

        // Increment iterator
        ++it;
    }
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

inline bool CharInfoHandler::compare(const CHAR_INFO* const first, const CHAR_INFO* const second)
{
    return first->Char.UnicodeChar == second->Char.UnicodeChar && first->Attributes == second->Attributes;
}

inline bool CharInfoHandler::compare(const CHAR_INFO* const first, WCHAR secondCharacter, const WORD secondAttributes)
{
    return first->Char.UnicodeChar == secondCharacter && first->Attributes == secondAttributes;
}