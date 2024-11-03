#pragma once
#include "pch.h"
#include "Tilemap.h"
#include "Player.h"
#include "FlipbookActor.h"

enum class ActorType
{
	Player,
	Cactus,
	Barrel
};

class Scene
{
public:
	Scene();
	virtual ~Scene();

	void Init();
	void Update();
	Player* FindPlayerById(uint32 id);

	void Render(Gdiplus::Graphics* g);

	Player* GetLocalPlayer();
	Player* SpawnLocalPlayer();
	void UpdateLocalPlayer();
	void SendPlayerDataToServer();
	Actor* Spawn(ActorType type, Vec2Int size, Vec2Int pos, uint32 id);

private:
	Gdiplus::Image* _bgImage=nullptr;
	unordered_map<wstring, Image*>		_images;
	unordered_map<wstring, Tilemap*>	_tilemaps;
	unordered_map<uint32, Player*>		_players;
	
	unordered_set<Actor*> _actors;
	Player* _localPlayer;
	Vec2Int Size{ 1920, 1024 };
	Vec2 _startPos = { 1920, 1024 };
};

