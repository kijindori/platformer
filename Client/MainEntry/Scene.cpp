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

	// Main Character
	Locator::GetLoader()->LoadImage(L"C:\\zinx7\\Resource\\platformer-sprites\\MainCharacters\\2\\PlayerDown.bmp", L"Test.png");
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

	/* ���� �÷��̾� ĳ���� ���� */
	Player* localPlayer = SpawnLocalPlayer();
	Locator::provideCamera(new Camera(localPlayer));

	/* ������Ʈ ���� */
	Spawn(ActorType::Barrel, Vec2Int(64, 64), Vec2Int(100, 873), 1);
	Spawn(ActorType::Barrel, Vec2Int(64, 64), Vec2Int(83, 873), 2);
	Spawn(ActorType::Cactus, Vec2Int(64, 64), Vec2Int(370, 770), 3);

	/* ��� */
	_bgImage = (Gdiplus::Image*)Locator::GetLoader()->FindImage(L"IMG__BG");

}

void Scene::Update()
{
	_localPlayer->Update();
	SendPlayerDataToServer();

	Locator::GetSession()->UpdateScene(this);
	/*for (Actor* actor : _actors)
		actor->Update();*/
}

Player* Scene::FindPlayerById(uint32 id)
{
	auto it = _players.find(id);

	if (it == _players.end())
		return nullptr;

	return it->second;
}

void Scene::UpdatePlayer(Player* player)
{

}

void Scene::Render(Gdiplus::Graphics* g)
{
	// ī�޶��� ��ġ�� �������� ȭ���� �׸��ϴ�.
	Locator::GetCamera()->UpdatePos();
	Vec2Int camPos = Locator::GetCamera()->GetPos();

	// ��� �̹���
	Rect drawRect(0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
	if (_bgImage && _bgImage->GetLastStatus() == Ok) {
		g->DrawImage(_bgImage, drawRect, camPos.x - CLIENT_WIDTH / 2, camPos.y - CLIENT_HEIGHT / 2 , CLIENT_WIDTH, CLIENT_HEIGHT, UnitPixel);
	}
	
	for (Actor* actor : _actors)
		actor->Render(g);
	_localPlayer->Render(g);
}

Player* Scene::GetLocalPlayer()
{
	return _localPlayer;
}

Player* Scene::SpawnLocalPlayer()
{
	_localPlayer = new Player(Locator::GetLoader()->FindFlipbook(L"Idle.png"), Vec2Int(100, 100));
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
	Session* session = Locator::GetSession();
	BYTE data[sizeof(PlayerData)];

	_localPlayer->Serialize(data);
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
		spawnedActor = (Actor*) new Cactus(Locator::GetLoader()->FindFlipbook(L"E2_Idle.png"), pos);
		break;

	case ActorType::Barrel:
		spawnedActor = (Actor*) new Barrel(Locator::GetLoader()->FindFlipbook(L"E3_Idle.png"), pos);
		break;
	}

	if (spawnedActor)
	{
		spawnedActor->SetId(id);
		spawnedActor->SetSize(size);
		_actors.insert(spawnedActor);
	}
	
	return spawnedActor;
}