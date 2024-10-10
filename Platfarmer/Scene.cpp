#include "pch.h"
#include "Scene.h"
#include "Locator.h"
#include "Collision.h"
#include "Cactus.h"
#include "Barrel.h"



Scene::Scene() {}
Scene::~Scene() {}


void Scene::Init()
{	
	


	//Load Image

	
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\save.png",L"IMG__BG");

	//Main Character
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

	//Enemy

	//Cactus
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\2\\Idle.png", L"E2_Idle.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\2\\Run.png", L"E2_Run.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\2\\Hit.png", L"E2_Hit.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\2\\Fall.png", L"E2_Fall.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\2\\Jump.png", L"E2_Jump.png");

	Locator::GetLoader()->CreateFlipbook(L"E2_Idle.png", 0, 0, 10, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E2_Run.png", 0, 0, 11, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E2_Hit.png", 0, 0, 4, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E2_Fall.png", 0, 0, 0, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E2_Jump.png", 0, 0, 0, Vec2Int{ 48,48 });

	//Barrel
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\3\\Idle.png", L"E3_Idle.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\3\\Walk.png", L"E3_Walk.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\3\\Hit.png", L"E3_Hit.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\3\\Stun.png", L"E3_Stun.png");
	Locator::GetLoader()->LoadImage(L"C:\\z2x7\\Resource\\platformer-sprites\\Enemies\\3\\Charge.png", L"E3_Charge.png");

	Locator::GetLoader()->CreateFlipbook(L"E3_Idle.png", 0, 0, 10, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E3_Walk.png", 0, 0, 10, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E3_Hit.png", 0, 0, 4, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E3_Stun.png", 0, 0, 7, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E3_Charge.png", 0, 0, 10, Vec2Int{ 48,48 });

	/* Player */
	Player* localPlayer = new Player(Locator::GetLoader()->FindFlipbook(L"Idle.png"));
	localPlayer->SetPos(Vec2Int{ 100,100 });
	_actors.push_back(localPlayer);

	/* Enemies */
	Cactus* cactus = new Cactus(Locator::GetLoader()->FindFlipbook(L"E2_Run.png"));
	cactus->SetPos(Vec2Int{ 1000,892 });
	cactus->SetSize(Vec2Int{ 64,64 });
	_actors.push_back(cactus);

	Barrel* barrel = new Barrel(Locator::GetLoader()->FindFlipbook(L"E3_Stun.png"));
	barrel->SetPos(Vec2Int{ 900,892 });
	barrel->SetSize(Vec2Int{ 64,64 });
	_actors.push_back(barrel);

	/* Camera */
	Locator::provideCamera(new Camera(localPlayer));

	/* Background Image */
	_bgImage = (Gdiplus::Image*)Locator::GetLoader()->FindImage(L"IMG__BG");

	/* Load TILEMAP */
	Locator::GetLoader()->LoadTilemap(L"C:\\z2x7\\Resource\\1lvl-col.txt", L"lv1-col");

	/* WALL */
	Tilemap* tm = Locator::GetLoader()->FindTilemap(L"lv1-col");

}

void Scene::Update()
{
	for(Actor* actor : _actors)
		actor->Update();
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

	for (Actor* actor : _actors)
		actor->Render(g);
	
}