#pragma once
#include "pch.h"


class Actor;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render(Graphics* g) = 0;

	Actor* GetOwner();
	void SetOwner(Actor* actor);

	Vec2Int GetSize();
	void SetSize(Vec2Int size);
	Vec2Int GetRelativePos();
	void SetRelativePos(Vec2Int pos);
	Vec2Int GetAbsolutePos();
	void SetAbsolutePos(Vec2Int apos);
	virtual void UpdateAbsolutePos();


private:
	Actor* _owner = nullptr;
	Vec2Int _rPos{ 0,0 };
	Vec2Int _aPos{ 0,0 };
	Vec2Int _size{ 32,32 };
};

