#pragma once
#include "FlipbookActor.h"
#include "Collider.h"
#include "Tilemap.h"

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
	Stuck,


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

	virtual void OnBeginCollision(Collider* src, Collider* dest) override;
	virtual void OnColliding(Collider* src, Collider* dest) override;
	virtual void OnEndCollision(Collider* src, Collider* dest) override;

	PlayerState CheckOverlap(RECT& other, RECT& intersect);

	PlayerState GetState();
	void SetState(PlayerState st);

private:
	void UpdateState();
	bool CanGo(int32 cellX, int32 cellY, vector<vector<Tile>>& tiles);
	void StopX();
	void StopY();
	void Run(int32 dir);
	void Jump();
	void Hit();
	void Drag();
	void TickGravity();
	void TickStep();
	void SlowMove(int _dir);


private:
	int32 _dir = 1;
	int32 _gravity = 1;
	Vec2Int _v{ 0,3 };

	PlayerState _state = PlayerState::Idle;
	vector<Flipbook*> _fbs;
	
};

