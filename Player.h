#pragma once
#include "FlipbookActor.h"

enum class PlayerState
{
	Idle,
	Run,
	Hit,
	Jump,
	DoubleJump,
	WallJump,
	Fall,

	End,
};

class Player : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Player(Flipbook* fb);
	virtual ~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Graphics* g) override;

	void SetState(PlayerState st);
private:
	int32 _dir = 1;
	int32 _gravity = 0;
	Vec2 _v{ 3,0 };

	PlayerState _state = PlayerState::Idle;
	vector<Flipbook*> _fbs;
};

