#include "pch.h"
#include "Scene.h"
#include "Locator.h"
#include "Collision.h"



Scene::Scene() {}
Scene::~Scene() {}


void Scene::Init()
{	
	


	//Load image
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\save.png",L"IMG__BG");
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

	/* Player */
	_actor = new Player(Locator::GetLoader()->FindFlipbook(L"Idle.png"));
	_actor->SetPos(Vec2Int{ 100,100 });

	/* Camera */
	Locator::provideCamera(new Camera(_actor));

	/* Background Image */
	_bgImage = (Gdiplus::Image*)Locator::GetLoader()->FindImage(L"IMG__BG");

	/* Load TILEMAP */
	Locator::GetLoader()->LoadTilemap(L"C:\\z2x7\\Resource\\1lvl-col.txt", L"lv1-col");

	/* WALL */
	Tilemap* tm = Locator::GetLoader()->FindTilemap(L"lv1-col");

}

void Scene::Update()
{
	
	_actor->Update();

	for(Actor* col : _col)
		col->Update();

	
	
}

void Scene::Render(Gdiplus::Graphics* g)
{

	Locator::GetCamera()->UpdatePos();
	Vec2Int camPos = Locator::GetCamera()->GetPos();

	//BACKGROUND IMAGE
	Rect drawRect(0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
	if (_bgImage && _bgImage->GetLastStatus() == Ok) {
		g->DrawImage(_bgImage, drawRect, camPos.x - CLIENT_WIDTH / 2, camPos.y - CLIENT_HEIGHT / 2 , CLIENT_WIDTH, CLIENT_HEIGHT, UnitPixel);
	}

	_actor->Render(g);
	for (Actor* col : _col)
		col->Render(g);
	
	
}