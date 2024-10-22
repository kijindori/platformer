#include "pch.h"
#include "Component.h"
#include "Actor.h"


Component::Component()
{
}

Component::~Component()
{

}


Actor* Component::GetOwner()
{
	return _owner;
}

void Component::SetOwner(Actor* owner)
{
	_owner = owner;
}

Vec2Int Component::GetSize()
{
	return _size;
}

void Component::SetSize(Vec2Int size)
{
	_size = size;
}

Vec2Int Component::GetRelativePos()
{
	return _rPos;
}

void Component::SetRelativePos(Vec2Int pos)
{
	_rPos = pos;
}

Vec2Int Component::GetAbsolutePos()
{
	return _aPos;
}

void Component::SetAbsolutePos(Vec2Int apos)
{
	_aPos = apos;
}

void Component::UpdateAbsolutePos()
{
	_aPos = _owner->GetPos() + GetRelativePos();
}


