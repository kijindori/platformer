#pragma once
#include "pch.h"
#include "Scene.h"
#include "Session.h"
class Game
{
public:
	Game()	{}
	~Game() {}
	void	Init(HWND hWnd);
	void	Update();
	void	Render();


	ULONG_PTR			gdiplusToken	= NULL;
	Gdiplus::Graphics*	_g				= NULL;
private:
	/* Init() */
	HWND	_hWnd			= NULL;
	HDC		_hdc			= NULL;
	HDC		_hdcBackBuffer	= NULL;
	HBITMAP _bitmap			= NULL;
	
	int32	_width			= 0;
	int32	_height			= 0;

	RECT	_clientRect{0,0};
	
};

