#include "pch.h"
#include "Collider.h"
#include "Locator.h"
#include "Collision.h"

Collider::Collider()
{
	Locator::GetCollisionService()->AddColliders(this);
}

Collider::~Collider()
{
	Locator::GetCollisionService()->RemoveCollider(this);
}

void Collider::Init()
{

}

void Collider::Update()
{
	UpdateAbsolutePos();

	Vec2Int aPos = GetAbsolutePos();
	Vec2Int size = GetSize();
	_r = { aPos.x, aPos.y, aPos.x + size.x, aPos.y + size.y };
}

void Collider::Render(Graphics* g)
{
	Vec2Int pos = GetOwner()->GetPos();
	Vec2Int size = GetSize();
	Gdiplus::Pen pen(Gdiplus::Color(255,255,0), 1);
	//
	g->DrawRectangle(&pen, pos.x - size.x / 2, pos.y - size.y , size.x , size.y);
}

bool Collider::Find(Collider* collider)
{
	if (collider == nullptr)
		return false;

	if (_collided.find(collider) == _collided.end())
		return false;

	return true;
	
}

void Collider::InsertCollided(Collider* collider)
{
	_collided.insert(collider);
}

void Collider::RemoveCollided(Collider* collider)
{
	assert(Find(collider));

	_collided.erase(collider);
}

void Collider::UpdateAbsolutePos()
{
	Super::UpdateAbsolutePos();
	Vec2Int _apos = GetAbsolutePos();
	Vec2Int _size = GetSize();

	_r = { _apos.x, _apos.y, _apos.x + _size.x, _apos.y + _size.y };
}


bool Collider::CheckCollision(Collider* other)
{
	BYTE groupBit = 1 << (uint8) other->_collisionGroup;
	return groupBit & _flag;
}



void Collider::SetFlag(CollisionGroup g)
{
	BYTE groupBit = 1 << (uint8)g;

	_flag |= groupBit;
}

void Collider::SetGroup(CollisionGroup group)
{
	_collisionGroup = (BYTE) group;
}

void Collider::ResetFlag()
{
	_flag = 0x00;
}

RECT* Collider::GetRect()
{
	return &_r;
}
