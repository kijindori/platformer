#pragma once
#include "pch.h"
#include "Tilemap.h"
#include "Player.h"
#include "FlipbookActor.h"
class Scene
{
public:
	Scene();
	virtual ~Scene();

	void Init();
	void Update();
	void Render(Gdiplus::Graphics* g);

private:
	Gdiplus::Image* _bgImage=nullptr;
	unordered_map<wstring, Image*> _images;
	unordered_map<wstring, Tilemap*> _tilemaps;
	
	Player* _actor = nullptr;
	vector<Actor*> _col;
	Vec2Int Size{ 1920, 1024 };
	Vec2 _startPos = { 1920, 1024 };
};

