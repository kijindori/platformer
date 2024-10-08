#pragma once
#include "Component.h"
#include "Actor.h"

class Actor;

enum class CollisionGroup
{
	None,
	Player,
	Ground,
	Object,
	Interactive,
};

class Collider : public Component
{
	using Super = Component;
public:
	Collider();

	virtual ~Collider() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Graphics* g) override;

	bool Find(Collider* collider);
	void InsertCollided(Collider* collider);
	void RemoveCollided(Collider* collider);

	virtual void UpdateAbsolutePos() override;

	bool CheckCollision(Collider* other);
	void SetFlag(CollisionGroup g);
	void SetGroup(CollisionGroup group);
	void ResetFlag();

	RECT* GetRect();

	BYTE _flag = 0x01;
	BYTE _collisionGroup = 0;
private:
	RECT _r{ 0,0,32,32 };
	bool _debug = false;
	unordered_set<Collider*> _collided;
};

