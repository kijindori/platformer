#include "pch.h"
#include "Collision.h"
#include "Locator.h"

AudioService* Locator::_audioService = nullptr;
Loader* Locator::_loader = nullptr;
InputHandler* Locator::_input = nullptr;
Collision* Locator::_collision = nullptr;
Camera* Locator::_cam = nullptr;
Timer* Locator::_timer = nullptr;

void Locator::Init(HWND hWnd)
{
	Locator::provideLoader(new Loader());
	Locator::provideInputService(new InputHandler(hWnd));
	Locator::provideCollisionService(new Collision());
	Locator::provideTimer(new Timer());
}
