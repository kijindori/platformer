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


private:
	int32 _dir = 1;
	int32 _gravity = 1.5;
	Vec2Int _v{ 0,3 };

	PlayerState _state = PlayerState::Idle;
	vector<Flipbook*> _fbs;
	
};

