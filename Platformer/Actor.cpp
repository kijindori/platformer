#include "pch.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor() {}
Actor::~Actor() {}

void Actor::Init()
{

}


void Actor::Update()
{
	for (Component* comp : _comp)
	{
		if (comp == nullptr)
			continue;

		comp->Update();
	}
}


void Actor::Render(Gdiplus::Graphics* g)
{
	for (Component* comp : _comp)
	{
		if (comp == nullptr)
			continue;

		comp->Render(g);
	}
}


Vec2Int Actor::GetPos()
{
	return _pos;
}

void Actor::SetPos(Vec2Int pos)
{
	_pos = pos;
	for (Component* comp : _comp)
		comp->UpdateAbsolutePos();
}


Vec2Int Actor::GetSize()
{
	return _size;
}


void Actor::SetSize(Vec2Int size)
{
	_size = size;
}

int32 Actor::GetLayer()
{
	return _layer;
}

void Actor::SetLayer(int32 layer)
{
	_layer = layer;
}

double Actor::GetTimer()
{
	return _timer;
}

void Actor::SetTimer(double timer)
{
	_timer = timer;
}

void Actor::AddComponent(Component* comp)
{
	comp->SetOwner(this);
	comp->UpdateAbsolutePos();
	_comp.push_back(comp);
}

void Actor::OnBeginOverlapped(Collider* src, Collider* dest)
{
}

void Actor::OnOverlapping(Collider* src, Collider* dest)
{
}

void Actor::OnEndOverlapped(Collider* src, Collider* dest)
{
}

