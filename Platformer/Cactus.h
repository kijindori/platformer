#pragma once
#include "FlipbookActor.h"

enum class CactusState
{
	Idle,
	Run,
	Hit,
	Fall,
	Jump,

	End,
};


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

private:
	vector<Flipbook*> _fbs;

};

