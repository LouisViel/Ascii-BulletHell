#include "../include/InputHandler.h"

InputHandler* InputHandler::singleton = nullptr;

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

const InputHandler::InputKey& InputHandler::getCurrentKey()
{
    return singleton->currentKey;
}

InputHandler::InputHandler() : currentKey(InputKey::None)
{
    hInput = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);
    inputRecord = new INPUT_RECORD();
    inputEventsRead = new DWORD();
    singleton = this;
}

InputHandler::~InputHandler()
{
    delete inputRecord;
    delete inputEventsRead;
    singleton = nullptr;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void InputHandler::updateKeyboardInput()
{
    if (isKeyPressed('Z') || isKeyPressed('W') || isKeyPressed(VK_UP)) currentKey = InputKey::Up;
    else if (isKeyPressed('Q') || isKeyPressed('A') || isKeyPressed(VK_LEFT)) currentKey = InputKey::Left;
    else if (isKeyPressed('S') || isKeyPressed(VK_DOWN)) currentKey = InputKey::Down;
    else if (isKeyPressed('D') || isKeyPressed(VK_RIGHT)) currentKey = InputKey::Right;
    else currentKey = InputKey::None;
}

inline bool InputHandler::isKeyPressed(unsigned short key)
{
    return (GetAsyncKeyState(key) & 0x8000);
}