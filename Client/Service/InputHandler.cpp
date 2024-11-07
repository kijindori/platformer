#include "pch.h"
#include "InputHandler.h"


InputHandler::InputHandler(HWND hWnd)
{
	_hWnd = hWnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None);
}
InputHandler::~InputHandler() {}


void InputHandler::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};

	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (UINT32 i = 0; i < KEY_TYPE_COUNT; i++)
	{
		// 해당 키가 눌러져있는지 아닌지 확인하고,
		// 상태를 업데이트 합니다.
		KeyState& state = _states[i];

		if (asciiKeys[i] & 0x80)
		{
			if (state == KeyState::Down || state == KeyState::Press)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		else
		{
			if (state == KeyState::Down || state == KeyState::Press)
				state = KeyState::Up;
			else
				state = KeyState::None;
		}

	}

	::GetCursorPos(&_cursorPos);
	::ScreenToClient(_hWnd, &_cursorPos);
}

bool InputHandler::IsKeyPressed(KeyType key)
{
	return _states[static_cast<uint8>(key)] == KeyState::Press ;
}

bool InputHandler::IsKeyDown(KeyType key)
{
	return _states[static_cast<uint8>(key)] == KeyState::Down;
}

bool InputHandler::IsKeyIdle(KeyType key)
{
	return _states[static_cast<uint8>(key)] == KeyState::None;
}

bool InputHandler::IsKeyUp(KeyType key)
{
	return _states[static_cast<uint8>(key)] == KeyState::Up;
}
