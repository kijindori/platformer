#pragma once
#include "pch.h"
#include "Collider.h"

class Collision

{
public:
	Collision();
	~Collision();

	bool Check(Collider* src, Collider* dest);
	void Iterate();

	void AddColliders(Collider* newCollider);
	void RemoveCollider(Collider* coll);
	

private:
	vector<Collider*> _colliders;
};

