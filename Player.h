#pragma once
#include "FlipbookActor.h"
#include "Collider.h"

enum class PlayerState
{
	Idle,
	Ready,
	Run,
	Hit,
	Jump,
	DoubleJump,
	WallJump,
	Fall,
	OnGround,
	UnderGround,
	LeftGround,
	RightGround,


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

	virtual void OnBeginOverlapped(Collider* src, Collider* dest) override;
	virtual void OnOverlapping(Collider* src, Collider* dest) override;
	virtual void OnEndOverlapped(Collider* src, Collider* dest) override;

	PlayerState CheckOverlap(RECT& other, RECT& intersect);

	void SetState(PlayerState st);
private:
	int32 _dir = 1;
	int32 _gravity = 3;
	Vec2 _v{ 0,0 };

	PlayerState _state = PlayerState::Idle;
	vector<Flipbook*> _fbs;
	
};

