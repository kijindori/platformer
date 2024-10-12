#include "pch.h"
#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
	for (Collider* coll : _colliders)
		delete coll;
}

bool Collision::Check(Collider* src, Collider* dest)
{
	RECT intersect{};
	if (::IntersectRect(&intersect, src->GetRect(), dest->GetRect()))
		return true;
}

void Collision::Iterate()
{
	for (int i = 0; i < _colliders.size(); i++)
	{
		for (int j = i + 1; j < _colliders.size(); j++)
		{
			Collider* src = _colliders[i];
			Collider* dest = _colliders[j];


			if (src->CheckCollision(dest) == false || dest->CheckCollision(src) == false)
				continue;

			if (Check(src, dest))
			{
				if (src->Find(dest))
				{
					src->GetOwner()->OnOverlapping(src, dest);
					dest->GetOwner()->OnOverlapping(src, dest);
				}
				else
				{
					src->GetOwner()->OnBeginOverlapped(src, dest);
					dest->GetOwner()->OnBeginOverlapped(src, dest);
					src->InsertCollided(dest);
					dest->InsertCollided(src);

				}
			}
			else
			{
				if (src->Find(dest))
				{
					src->GetOwner()->OnEndOverlapped(src, dest);
					dest->GetOwner()->OnEndOverlapped(src, dest);
					src->RemoveCollided(dest);
					dest->RemoveCollided(src);
				}
			}
		}
	}
}

void Collision::AddColliders(Collider* newCollider)
{
	_colliders.push_back(newCollider);
}

void Collision::RemoveCollider(Collider* coll)
{
	auto newEnd = remove(_colliders.begin(), _colliders.end(), coll);
	_colliders.erase(newEnd, _colliders.end());
}
