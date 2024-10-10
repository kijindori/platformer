#pragma once
#include "FlipbookActor.h"

class Cactus : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Cactus(Flipbook* fb);
	virtual ~Cactus();

	virtual void Init();
	virtual void Update();
	virtual void Render(Graphics* g) override;

private:
	void Hit();

};

