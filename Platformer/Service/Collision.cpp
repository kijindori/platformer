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
					src->GetOwner()->OnColliding(src, dest);
					dest->GetOwner()->OnColliding(src, dest);
				}
				else
				{
					src->GetOwner()->OnBeginCollision(src, dest);
					dest->GetOwner()->OnBeginCollision(src, dest);
					src->InsertCollided(dest);
					dest->InsertCollided(src);

				}
			}
			else
			{
				if (src->Find(dest))
				{
					src->GetOwner()->OnEndCollision(src, dest);
					dest->GetOwner()->OnEndCollision(src, dest);
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
