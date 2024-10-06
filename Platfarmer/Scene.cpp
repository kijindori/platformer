#include "pch.h"
#include "Scene.h"
#include "Locator.h"
#include "Collision.h"



Scene::Scene() {}
Scene::~Scene() {}


void Scene::Init()
{	
	//Load TILEMAP

	Locator::GetLoader()->LoadTilemap(L"C:\\z2x7\\Resource\\1lvl-col.txt", L"lv1-col");


	//Load image
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\asteroid.png",L"IMG__BG");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Locations\\Tiles\\Tile_01.png",L"Tile_01.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\MainCharacters\\1\\Run.png", L"Run.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\MainCharacters\\1\\Idle.png", L"Idle.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\MainCharacters\\1\\Hit.png", L"Hit.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\MainCharacters\\1\\Fall.png", L"Fall.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\MainCharacters\\1\\Jump.png", L"Jump.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\MainCharacters\\1\\Double_Jump.png", L"Double_Jump.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\MainCharacters\\1\\Wall_Jump.png", L"Wall_Jump.png");

	Locator::GetLoader()->CreateFlipbook(L"Run.png", 0, 0, 11, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Idle.png", 0, 0, 10, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Hit.png", 0, 0, 6, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Fall.png", 0, 0, 0, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Jump.png", 0, 0, 0, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Double_Jump.png", 0, 0, 5, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Wall_Jump.png", 0, 0, 6, Vec2Int{ 32,32 });

	_actor = new Player(Locator::GetLoader()->FindFlipbook(L"Idle.png"));
	_actor->SetPos(Vec2Int{ 100,100 });

	_bgImage = (Gdiplus::Image*)Locator::GetLoader()->FindImage(L"IMG__BG");


	// WALL
	Tilemap* tm = Locator::GetLoader()->FindTilemap(L"lv1-col");
	auto& tiles = tm->GetTiles();
	Vec2Int msize = tm->GetMapSize();
	Vec2Int tileSize = tm->GetTileSize();

	for (int y = 0; y < msize.y; y++)
	{
		for (int x = 0; x < msize.x; x++)
		{
			int value = tiles[y][x].value;

			if (value == 1)
			{
				//FlipbookActor* col = new FlipbookActor(Locator::GetLoader()->FindFlipbook(L"Idle.png"));
				Actor* col = new Actor();
				col->SetPos(Vec2Int(x * tileSize.x, y * tileSize.y));
				col->AddComponent(new Collider());
				_col.push_back(col);
			}
			
		}
	}

}

void Scene::Update()
{
	
	_actor->Update();

	for(Actor* col : _col)
		col->Update();

	
	
}

void Scene::Render(Gdiplus::Graphics* g)
{
	//BACKGROUND IMAGE
	Rect drawRect(0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
	if (_bgImage && _bgImage->GetLastStatus() == Ok) {
		g->DrawImage(_bgImage, drawRect, 0, 0, _bgImage->GetWidth(), _bgImage->GetHeight(), UnitPixel);
	}

	_actor->Render(g);
	for (Actor* col : _col)
		col->Render(g);
	
	
}