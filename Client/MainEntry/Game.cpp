#include "pch.h"
#include "Game.h"
#include "Locator.h"
#include "Loader.h"
#include "AudioService.h"
#include "TilemapService.h"
#include "Collision.h"
#include "Session.h"

void Game::Init(HWND hWnd)
{

	/* WINAPI ���� �ʱ�ȭ */
	_hWnd = hWnd;
	_hdc = ::GetDC(hWnd);
	_hdcBackBuffer = CreateCompatibleDC(_hdc);

	::GetClientRect(hWnd, &_clientRect);

	_width = _clientRect.right - _clientRect.left;
	_height = _clientRect.bottom - _clientRect.top;
	
	/* �� ���� �ʱ�ȭ */
	HBITMAP backbit = CreateCompatibleBitmap(_hdc, _width, _height);
	HBITMAP oldBackBit = (HBITMAP)SelectObject(_hdcBackBuffer, backbit);
	DeleteObject(oldBackBit);

	/* Gdiplus �ʱ�ȭ */
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	_g = Gdiplus::Graphics::FromHDC(_hdcBackBuffer);


	/* ���� �ʱ�ȭ */
	Locator::Init(_hWnd);

	/* Scene �ʱ�ȭ : ���ҽ��� �ε��ϰ� Actor ���� ��ġ�մϴ�. */
	Locator::GetScene()->Init();
}



void Game::Update()
{
	/* Ű���� �Է� ���� �� ���콺 �Է� ���� ������Ʈ */
	Locator::GetInputService()->Update();

	/* Interval ������Ʈ */
	Locator::GetTimer()->Update();

	/* Scene ������Ʈ -> Actor ������Ʈ */
	Locator::GetScene()->Update();

	/* �浹 ���� */
	Locator::GetCollisionService()->Iterate();
}

void Game::Render()
{
	/* Graphics _g : �ĸ� ���ۿ� ������ */
	Locator::GetScene()->Render(_g);

	// �ĸ� ���۸� ���� ���۷� �ű�� �ʱ�ȭ
	BitBlt(_hdc, 0, 0, _width, _height, _hdcBackBuffer, 0, 0, SRCCOPY);
	PatBlt(_hdcBackBuffer, 0, 0, _width, _height, BLACKNESS);
}


