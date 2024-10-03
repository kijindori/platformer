#include "pch.h"
#include "Game.h"
#include "Locator.h"
#include "ImageService.h"
#include "AudioService.h"
#include "TilemapService.h"

void Game::Init(HWND hWnd)
{
	_hWnd = hWnd;
	_hdc = ::GetDC(hWnd);
	_hdcBackBuffer = CreateCompatibleDC(_hdc);

	::GetClientRect(hWnd, &_clientRect);

	_width = _clientRect.right - _clientRect.left;
	_height = _clientRect.bottom - _clientRect.top;
	
	// back buffer
	HBITMAP backbit = CreateCompatibleBitmap(_hdc, _width, _height);
	HBITMAP oldBackBit = (HBITMAP)SelectObject(_hdcBackBuffer, backbit);
	DeleteObject(oldBackBit);

	// GDI+ 
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	_g = Gdiplus::Graphics::FromHDC(_hdcBackBuffer);


	// Service
	Locator::provideImageService(new ImageService());
	Locator::provideTilemapService(new TilemapService());
	Locator::provideInputService(new InputHandler(_hWnd));


	// Deligate
	_scene->Init();
}



void Game::Update()
{
	Locator::GetInputService()->Update();
	_scene->Update();
}

void Game::Render()
{
	
	_scene->Render(_g);


	BitBlt(_hdc, 0, 0, _width, _height, _hdcBackBuffer, 0, 0, SRCCOPY);
	PatBlt(_hdcBackBuffer, 0, 0, _width, _height, BLACKNESS);
}