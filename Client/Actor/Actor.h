#pragma once
#include "pch.h"

class Component;
class Collider;

class Actor
{
public:
	Actor();
	virtual ~Actor();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(Gdiplus::Graphics* g);

	uint32	GetId();
	void	SetId(uint32 id);

	Vec2Int GetPos();
	void	SetPos(Vec2Int pos);

	Vec2Int GetSize();
	void	SetSize(Vec2Int size);

	int32	GetLayer();
	void	SetLayer(int32 layer);

	double	GetTimer();
	void	SetTimer(double timer);

	double	GetHitTimer() { return _hitTimer; }
	void	SetHitTimer(double hitTimer) { _hitTimer = hitTimer;  }

	Collider* GetCollider();

	/* 컴포넌트 추가 : 현재는 충돌체만 추가 */
	void AddComponent(Component* comp);

	virtual void OnBeginCollision(Collider* src, Collider* dest);
	virtual void OnColliding(Collider* src, Collider* dest);
	virtual void OnEndCollision(Collider* src, Collider* dest);

private:
	uint32	_id			= 0;
	int32	_layer		= 0;
	double	_timer		= 0;
	double	_hitTimer	= 0;
	Vec2Int _pos		{0,0};
	Vec2Int _size		{32,32};
	

	vector<Component*> _comp;
};

