#pragma once
#include "pch.h"
#include "Scene.h"

class Game
{
public:
	Game()	{}
	~Game() {}
	void Init(HWND hWnd);
	void Update();
	void Render();

private:
	HWND _hWnd;
	HDC _hdc;
	HDC _hdcBackBuffer;
	HBITMAP _bitmap;
	Gdiplus::Graphics* _g;

	int32 _width=0;
	int32 _height=0;

	RECT _clientRect;
	Scene* _scene = new Scene();
};

