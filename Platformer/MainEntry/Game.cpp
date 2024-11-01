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

	/* WINAPI 관련 초기화 */
	_hWnd = hWnd;
	_hdc = ::GetDC(hWnd);
	_hdcBackBuffer = CreateCompatibleDC(_hdc);

	::GetClientRect(hWnd, &_clientRect);

	_width = _clientRect.right - _clientRect.left;
	_height = _clientRect.bottom - _clientRect.top;
	
	/* 백 버퍼 초기화 */
	HBITMAP backbit = CreateCompatibleBitmap(_hdc, _width, _height);
	HBITMAP oldBackBit = (HBITMAP)SelectObject(_hdcBackBuffer, backbit);
	DeleteObject(oldBackBit);

	/* Gdiplus 초기화 */
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	_g = Gdiplus::Graphics::FromHDC(_hdcBackBuffer);


	/* 서비스 초기화 */
	Locator::Init(_hWnd);

	/* Scene 초기화 : 리소스를 로드하고 Actor 들을 배치합니다. */
	Locator::GetScene()->Init();
}



void Game::Update()
{
	/* 키보드 입력 상태 및 마우스 입력 상태 업데이트 */
	Locator::GetInputService()->Update();

	/* Interval 업데이트 */
	Locator::GetTimer()->Update();

	/* Scene 업데이트 -> Actor 업데이트 */
	Locator::GetScene()->Update();

	/* 충돌 감지 */
	Locator::GetCollisionService()->Iterate();
}

void Game::Render()
{
	/* Graphics _g : 후면 버퍼에 렌더링 */
	Locator::GetScene()->Render(_g);

	// 후면 버퍼를 전면 버퍼로 옮기고 초기화
	BitBlt(_hdc, 0, 0, _width, _height, _hdcBackBuffer, 0, 0, SRCCOPY);
	PatBlt(_hdcBackBuffer, 0, 0, _width, _height, BLACKNESS);
}


