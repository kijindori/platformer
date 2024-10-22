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
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\save.png",L"IMG__BG");

	//Main Character
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Run.png", L"Run.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Idle.png", L"Idle.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Hit.png", L"Hit.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Fall.png", L"Fall.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Jump.png", L"Jump.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Double_Jump.png", L"Double_Jump.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Wall_Jump.png", L"Wall_Jump.png");

	Locator::GetLoader()->CreateFlipbook(L"Run.png", 0, 0, 11, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Idle.png", 0, 0, 10, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Hit.png", 0, 0, 6, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Fall.png", 0, 0, 0, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Jump.png", 0, 0, 0, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Double_Jump.png", 0, 0, 5, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(L"Wall_Jump.png", 0, 0, 6, Vec2Int{ 32,32 });


	// Cactus
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\2\\Idle.png", L"E2_Idle.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\2\\Run.png", L"E2_Run.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\2\\Hit.png", L"E2_Hit.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\2\\Fall.png", L"E2_Fall.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\2\\Jump.png", L"E2_Jump.png");

	Locator::GetLoader()->CreateFlipbook(L"E2_Idle.png", 0, 0, 10, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E2_Run.png", 0, 0, 11, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E2_Hit.png", 0, 0, 4, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E2_Fall.png", 0, 0, 0, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E2_Jump.png", 0, 0, 0, Vec2Int{ 48,48 });

	// Barrel
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Idle.png", L"E3_Idle.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Walk.png", L"E3_Walk.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Hit.png", L"E3_Hit.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Stun.png", L"E3_Stun.png");
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Charge.png", L"E3_Charge.png");

	Locator::GetLoader()->CreateFlipbook(L"E3_Idle.png", 0, 0, 10, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E3_Walk.png", 0, 0, 10, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E3_Hit.png", 0, 0, 4, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E3_Stun.png", 0, 0, 7, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(L"E3_Charge.png", 0, 0, 10, Vec2Int{ 48,48 });

	/* Load TILEMAP */
	Locator::GetLoader()->LoadTilemap(L"C:\\zinx7\\Resource\\1lvl-col.txt", L"lv1-col");
	Tilemap* tm = Locator::GetLoader()->FindTilemap(L"lv1-col");

	/* 액터 배치 */
	Player* localPlayer = new Player(Locator::GetLoader()->FindFlipbook(L"Idle.png"));
	localPlayer->SetPos(Vec2Int{ 100,100 });
	_actors.push_back(localPlayer);

	Cactus* cactus0 = new Cactus(Locator::GetLoader()->FindFlipbook(L"E2_Run.png"));
	cactus0->SetPos(Vec2Int{ 993,892 });
	cactus0->SetSize(Vec2Int{ 64,64 });
	_actors.push_back(cactus0);

	Cactus* cactus1 = new Cactus(Locator::GetLoader()->FindFlipbook(L"E2_Run.png"));
	cactus1->SetPos(Vec2Int{ 963,892 });
	cactus1->SetSize(Vec2Int{ 64,64 });
	_actors.push_back(cactus1);

	Cactus* cactus2 = new Cactus(Locator::GetLoader()->FindFlipbook(L"E2_Run.png"));
	cactus2->SetPos(Vec2Int{ 1023,892 });
	cactus2->SetSize(Vec2Int{ 64,64 });
	_actors.push_back(cactus2);

	Barrel* barrel0 = new Barrel(Locator::GetLoader()->FindFlipbook(L"E3_Idle.png"));
	barrel0->SetPos(Vec2Int{ 770,247 });
	barrel0->SetSize(Vec2Int{ 64,64 });
	_actors.push_back(barrel0);

	Barrel* barrel1 = new Barrel(Locator::GetLoader()->FindFlipbook(L"E3_Idle.png"));
	barrel1->SetPos(Vec2Int{ 737,247 });
	barrel1->SetSize(Vec2Int{ 64,64 });
	_actors.push_back(barrel1);

	/* 카메라 */
	Locator::provideCamera(new Camera(localPlayer));

	/* 배경 */
	_bgImage = (Gdiplus::Image*)Locator::GetLoader()->FindImage(L"IMG__BG");

}

void Scene::Update()
{
	/* Actor 업데이트 */
	for(Actor* actor : _actors)
		actor->Update();
}

void Scene::Render(Gdiplus::Graphics* g)
{
	// 카메라의 위치를 기준으로 렌더링
	Locator::GetCamera()->UpdatePos();
	Vec2Int camPos = Locator::GetCamera()->GetPos();

	// 배경 이미지
	Rect drawRect(0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
	if (_bgImage && _bgImage->GetLastStatus() == Ok) {
		g->DrawImage(_bgImage, drawRect, camPos.x - CLIENT_WIDTH / 2, camPos.y - CLIENT_HEIGHT / 2 , CLIENT_WIDTH, CLIENT_HEIGHT, UnitPixel);
	}

	for (Actor* actor : _actors)
		actor->Render(g);
	
}