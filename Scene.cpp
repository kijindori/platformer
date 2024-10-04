#include "pch.h"
#include "Scene.h"
#include "Locator.h"
#include "Collision.h"


Scene::Scene() {}
Scene::~Scene() {}


void Scene::Init()
{	
	//Load image
	Locator::GetImageService()->LoadFile(L"C:\\EJ\\Resource\\asteroid.png",L"IMG__BG");
	Locator::GetImageService()->LoadFile(L"C:\\EJ\\Resource\\platformer-sprites\\Locations\\Tiles\\Tile_01.png",L"Tile_01.png");
	Locator::GetImageService()->LoadFile(L"C:\\EJ\\Resource\\platformer-sprites\\MainCharacters\\1\\Run.png", L"Run.png");
	Locator::GetImageService()->LoadFile(L"C:\\EJ\\Resource\\platformer-sprites\\MainCharacters\\1\\Idle.png", L"Idle.png");
	Locator::GetImageService()->LoadFile(L"C:\\EJ\\Resource\\platformer-sprites\\MainCharacters\\1\\Hit.png", L"Hit.png");
	Locator::GetImageService()->LoadFile(L"C:\\EJ\\Resource\\platformer-sprites\\MainCharacters\\1\\Fall.png", L"Fall.png");
	Locator::GetImageService()->LoadFile(L"C:\\EJ\\Resource\\platformer-sprites\\MainCharacters\\1\\Jump.png", L"Jump.png");
	Locator::GetImageService()->LoadFile(L"C:\\EJ\\Resource\\platformer-sprites\\MainCharacters\\1\\Double_Jump.png", L"Double_Jump.png");
	Locator::GetImageService()->LoadFile(L"C:\\EJ\\Resource\\platformer-sprites\\MainCharacters\\1\\Wall_Jump.png", L"Wall_Jump.png");

	Locator::GetImageService()->CreateFlipbook(L"Run.png", 0, 0, 11, Vec2Int{ 32,32 });
	Locator::GetImageService()->CreateFlipbook(L"Idle.png", 0, 0, 10, Vec2Int{ 32,32 });
	Locator::GetImageService()->CreateFlipbook(L"Hit.png", 0, 0, 6, Vec2Int{ 32,32 });
	Locator::GetImageService()->CreateFlipbook(L"Fall.png", 0, 0, 0, Vec2Int{ 32,32 });
	Locator::GetImageService()->CreateFlipbook(L"Jump.png", 0, 0, 0, Vec2Int{ 32,32 });
	Locator::GetImageService()->CreateFlipbook(L"Double_Jump.png", 0, 0, 5, Vec2Int{ 32,32 });
	Locator::GetImageService()->CreateFlipbook(L"Wall_Jump.png", 0, 0, 6, Vec2Int{ 32,32 });

	_actor = new Player(Locator::GetImageService()->FindFlipbook(L"Idle.png"));
	_actor->SetPos(Vec2Int{ 100,100 });

	_col = new FlipbookActor(Locator::GetImageService()->FindFlipbook(L"Idle.png"));
	_col->SetPos(Vec2Int{ 100,500 });
	_col->AddComponent(new Collider());
	_bgImage = (Gdiplus::Image*)Locator::GetImageService()->Find(L"IMG__BG");
}

void Scene::Update()
{
	
	_actor->Update();
	_col->Update();

	
	
}

void Scene::Render(Gdiplus::Graphics* g)
{
	//BACKGROUND IMAGE
	Rect drawRect(0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
	if (_bgImage && _bgImage->GetLastStatus() == Ok) {
		g->DrawImage(_bgImage, drawRect, 0, 0, _bgImage->GetWidth(), _bgImage->GetHeight(), UnitPixel);
	}

	_col->Render(g);
	_actor->Render(g);
	
}