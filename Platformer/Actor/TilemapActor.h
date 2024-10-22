#pragma once
#include "pch.h"
#include "Actor.h"
#include "Tilemap.h"


class TilemapActor : public Actor
{
	TilemapActor();
	virtual ~TilemapActor();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Graphics* g) override;

private:
	Tilemap* _tilemap = nullptr;
};
