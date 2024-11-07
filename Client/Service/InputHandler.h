#pragma once
#include "pch.h"

#define KEY_TYPE_COUNT 256

enum class KeyType
{
	Left = VK_LEFT,
	Up = VK_UP,
	Right = VK_RIGHT,
	Down = VK_DOWN,

	MouseLeft = VK_LBUTTON,
	MouseRight = VK_RBUTTON,

	KEY_1 = '1',

	Alt = VK_LMENU,
	Ctrl = VK_LCONTROL,
	Shift = VK_LSHIFT,

	Q = 'Q',
	W = 'W',
	E = 'E',
	R = 'R',
	A = 'A',
	S = 'S',
	D = 'D',
	F = 'F',

	SpaceBar = VK_SPACE,
};

enum class KeyState
{
	None,
	Down,
	Press,
	Up,

	End,
};


class InputHandler
{
public:
	InputHandler(HWND hWnd);
	~InputHandler();

	void Update();

	POINT GetCursorPoint() { return _cursorPos; }

	bool IsKeyPressed(KeyType key);
	bool IsKeyDown(KeyType key);
	bool IsKeyUp(KeyType key);
	bool IsKeyIdle(KeyType key);

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }

	HWND			 _hWnd		= 0;
	vector<KeyState> _states;
	POINT			 _cursorPos	{ 0,0 };
};

