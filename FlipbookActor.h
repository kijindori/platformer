#pragma once
#include "Actor.h"
#include "Sprite.h"


class FlipbookActor : public Actor
{
public:
	FlipbookActor(Flipbook* fb);
	virtual ~FlipbookActor();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Graphics* g) override;

	void SetFlipbook(Flipbook* fb);
	void SetIndex(uint32 index) { _index = index; }

private:
	Flipbook* _fb = nullptr;
	uint32 _index = 0;
};

