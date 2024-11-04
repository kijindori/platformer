#include "pch.h"
#include "Scene.h"
#include "Locator.h"
#include "Collision.h"
#include "Cactus.h"
#include "Barrel.h"

Scene::Scene() {}
Scene::~Scene() 
{
	for (pair<uint32, Player*> player : _players)
		delete player.second;

	for (Actor* actor : _actors)
		delete actor;

	delete _localPlayer;
	delete _bgImage;
}


void Scene::Init()
{	
	LoadResource();
	_bgImage = (Gdiplus::Image*)Locator::GetLoader()->FindImage(TEXT("IMG__BG"));

	/* 로컬 플레이어 캐릭터 생성 */
	Player* localPlayer = SpawnLocalPlayer();
	Locator::provideCamera(new Camera(localPlayer));

	/* 오브젝트 생성 */
	SpawnMonsters();
}

void Scene::Update()
{
	_localPlayer->Update();
	SendPlayerDataToServer();

	Locator::GetSession()->UpdateScene(this);

	for (Actor* actor : _actors)
		actor->Update();

}

Player* Scene::FindPlayerById(uint32 id)
{
	auto it = _players.find(id);

	if (it == _players.end())
		return nullptr;

	return it->second;
}


void Scene::Render(Gdiplus::Graphics* g)
{
	// 카메라의 위치를 기준으로 화면을 그립니다.
	Locator::GetCamera()->UpdatePos();
	Vec2Int camPos = Locator::GetCamera()->GetPos();

	// 배경 이미지 그리기
	Rect drawRect(0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
	if (_bgImage && _bgImage->GetLastStatus() == Ok) {
		g->DrawImage(_bgImage, drawRect, camPos.x - CLIENT_WIDTH / 2, camPos.y - CLIENT_HEIGHT / 2 , CLIENT_WIDTH, CLIENT_HEIGHT, UnitPixel);
	}
	
	for (Actor* actor : _actors)
		actor->Render(g);

	for (pair<uint32, Player*> player : _players)
		player.second->Render(g);

	_localPlayer->Render(g);
	_localPlayer->RenderIndicator(g);
}

void Scene::LoadResource()
{
	//Load Image
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\save.png"), TEXT("IMG__BG"));

	// Main Character
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\PlayerDown.bmp"), TEXT("Test.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Run.png"), TEXT("Run.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Idle.png"), TEXT("Idle.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Hit.png"), TEXT("Hit.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Fall.png"), TEXT("Fall.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Jump.png"), TEXT("Jump.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Double_Jump.png"), TEXT("Double_Jump.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\Wall_Jump.png"), TEXT("Wall_Jump.png"));

	Locator::GetLoader()->CreateFlipbook(TEXT("Run.png"), 0, 0, 11, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(TEXT("Idle.png"), 0, 0, 10, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(TEXT("Hit.png"), 0, 0, 6, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(TEXT("Fall.png"), 0, 0, 0, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(TEXT("Jump.png"), 0, 0, 0, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(TEXT("Double_Jump.png"), 0, 0, 5, Vec2Int{ 32,32 });
	Locator::GetLoader()->CreateFlipbook(TEXT("Wall_Jump.png"), 0, 0, 6, Vec2Int{ 32,32 });


	// Cactus
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\5\\Idle.png"), TEXT("E2_Idle.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\5\\Fly.png"), TEXT("E2_Fly.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\5\\Hit.png"), TEXT("E2_Hit.png"));
	//Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\5\\Fall.png"), TEXT("E2_Fall.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\5\\Attack.png"), TEXT("E2_Attack.png"));

	Locator::GetLoader()->CreateFlipbook(TEXT("E2_Idle.png"), 0, 0, 5, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(TEXT("E2_Fly.png"), 0, 0, 5, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(TEXT("E2_Hit.png"), 0, 0, 4, Vec2Int{ 48,48 });
	//Locator::GetLoader()->CreateFlipbook(TEXT("E2_Fall.png"), 0, 0, 0, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(TEXT("E2_Attack.png"), 0, 7, 0, Vec2Int{ 48,48 });

	// Barrel
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Idle.png"), TEXT("E3_Idle.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Walk.png"), TEXT("E3_Walk.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Hit.png"), TEXT("E3_Hit.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Stun.png"), TEXT("E3_Stun.png"));
	Locator::GetLoader()->LoadImage(TEXT("C:\\zinx7\\Resource\\platformer-sprites\\Enemies\\3\\Charge.png"), TEXT("E3_Charge.png"));

	Locator::GetLoader()->CreateFlipbook(TEXT("E3_Idle.png"), 0, 0, 10, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(TEXT("E3_Walk.png"), 0, 0, 10, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(TEXT("E3_Hit.png"), 0, 0, 4, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(TEXT("E3_Stun.png"), 0, 0, 7, Vec2Int{ 48,48 });
	Locator::GetLoader()->CreateFlipbook(TEXT("E3_Charge.png"), 0, 0, 10, Vec2Int{ 48,48 });

	/* Load TILEMAP */
	Locator::GetLoader()->LoadTilemap(TEXT("C:\\zinx7\\Resource\\1lvl-col.txt"), TEXT("lv1-col"));
	Tilemap* tm = Locator::GetLoader()->FindTilemap(TEXT("lv1-col"));
}

void Scene::SpawnMonsters()
{
	Spawn(ActorType::Barrel, Vec2Int(64, 64), Vec2Int(120, 873), 1);
	Spawn(ActorType::Barrel, Vec2Int(64, 64), Vec2Int(103, 873), 2);
	Spawn(ActorType::Cactus, Vec2Int(64, 64), Vec2Int(370, 893), 3);
	Spawn(ActorType::Cactus, Vec2Int(64, 64), Vec2Int(700, 893), 4);
	Spawn(ActorType::Barrel, Vec2Int(64, 64), Vec2Int(783, 257), 5);
	Spawn(ActorType::Barrel, Vec2Int(64, 64), Vec2Int(763, 257), 6);
}

Player* Scene::GetLocalPlayer()
{
	return _localPlayer;
}

Player* Scene::SpawnLocalPlayer()
{
	_localPlayer = new Player(Locator::GetLoader()->FindFlipbook(L"Idle.png"), Vec2Int(777, 300));
	_localPlayer->SetId(
		Locator::GetSession()->GetId()
	);

	return _localPlayer;
}

void Scene::UpdateLocalPlayer()
{
	_localPlayer->Update();
}

void Scene::SendPlayerDataToServer()
{
	Sleep(1);

	Session* session = Locator::GetSession();
	BYTE data[sizeof(PlayerData)];
	_localPlayer->Serialize(data, sizeof(data));
	session->Send(data, sizeof(data));
}

Actor* Scene::Spawn(ActorType type, Vec2Int size, Vec2Int pos, uint32 id)
{
	Actor* spawnedActor = nullptr;
	

	switch (type)
	{
	case ActorType::Player:
		spawnedActor = new Player(Locator::GetLoader()->FindFlipbook(L"Idle.png"), pos);
		_players.insert(make_pair(id, (Player*)spawnedActor));
		break;

	case ActorType::Cactus:
		spawnedActor = (Actor*) new Cactus(Locator::GetLoader()->FindFlipbook(L"E2_Fly.png"), pos);
		_actors.insert(spawnedActor);
		break;

	case ActorType::Barrel:
		spawnedActor = (Actor*) new Barrel(Locator::GetLoader()->FindFlipbook(L"E3_Idle.png"), pos);
		_actors.insert(spawnedActor);
		break;
	}

	if (spawnedActor)
	{
		spawnedActor->SetId(id);
		spawnedActor->SetSize(size);
	}
	
	return spawnedActor;
}
