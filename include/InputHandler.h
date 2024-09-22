#pragma once
#include <Windows.h>

class InputHandler
{
public:
	// Input Keys Enum
	enum class InputKey: int
	{
		None = 0,
		Up = 1,
		Right = 2,
		Down = 3,
		Left = 4
	};
	
	// Get Current Key Reference
	static const InputKey& getCurrentKey();
	void updateKeyboardInput();

	// Contructor Instructions
	InputHandler();
	~InputHandler();

private:
	static InputHandler* singleton;
	InputKey currentKey;

	INPUT_RECORD* inputRecord;
	DWORD* inputEventsRead;
	HANDLE hInput;

	inline bool isKeyPressed(unsigned short key);
};