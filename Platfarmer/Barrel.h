#pragma once
#include "FlipbookActor.h"


enum class BarrelState
{
	Idle,
	Walk,
	Hit,
	Stun,
	Charge,

	End,
};

class Barrel : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Barrel(Flipbook* fb);
	virtual ~Barrel();

	virtual void Init();
	virtual void Update();
	virtual void Render(Graphics* g) override;

private:
	void Hit();

private:
	vector<Flipbook*> _fbs;
};

