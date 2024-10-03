#include "pch.h"
#include "Actor.h"


Actor::Actor() {}
Actor::~Actor() {}



void Actor::Init()
{

}


void Actor::Update()
{

}


void Actor::Render(Gdiplus::Graphics* g)
{
	
}


Vec2Int Actor::GetPos()
{
	return _pos;
}

void Actor::SetPos(Vec2Int pos)
{
	_pos = pos;
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

