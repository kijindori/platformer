#pragma once
#include "Actor.h"
#include "Sprite.h"


class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor(Flipbook* fb);
	virtual ~FlipbookActor();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Graphics* g) override;

	virtual void OnBeginOverlapped(Collider* src, Collider* dest) override;
	virtual void OnOverlapping(Collider* src, Collider* dest) override;
	virtual void OnEndOverlapped(Collider* src, Collider* dest) override;

	void SetLeft(bool flag);
	void SetFlipbook(Flipbook* fb);
	void SetIndex(uint32 index) { _index = index; }

private:
	Flipbook* _fb = nullptr;
	uint32 _index = 0;
	bool _turnLeft = false;
};

