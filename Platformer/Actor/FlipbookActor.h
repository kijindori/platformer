#pragma once
#include "Actor.h"
#include "Sprite.h"
#include "Flipbook.h"


class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor(Flipbook* fb);
	virtual ~FlipbookActor();

	virtual void Init() ;
	virtual void Update() ;
	virtual void Render(Graphics* g) ;

	virtual void OnBeginCollision(Collider* src, Collider* dest) override;
	virtual void OnColliding(Collider* src, Collider* dest) override;
	virtual void OnEndCollision(Collider* src, Collider* dest) override;

	void SetLeft(bool flag);
	void SetFlipbook(Flipbook* fb);
	void SetIndex(uint32 index) { _index = index; }
	uint32 GetIndex();
private:
	Flipbook* _fb = nullptr;
	uint32 _index = 0;
	bool _turnLeft = false;
};

