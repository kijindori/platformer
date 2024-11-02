#pragma once
#include "pch.h"
#include "Player.h"

class Camera
{
public:
	Camera(Player* actor);
	~Camera();

	void AdjustActorPosition(Vec2Int* pos);
	Vec2Int GetPos();
	void SetPos(Vec2Int pos);
	void UpdatePos();

	Player* GetFocusedPlayer();
	void SetFocusedPlayer(Player* focus);
private:
	Vec2Int _pos{ 0, 0 };
	Player* _focus;
};

