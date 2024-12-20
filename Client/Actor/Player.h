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

struct PlayerData
{
	uint32		id;
	uint32		x;
	uint32		y;
	uint32		state;
	uint32		index;
	int32		direction;
};

class Player : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Player(Flipbook* fb, Vec2Int pos);
	virtual ~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Graphics* g) override;
	void RenderIndicator(Graphics* g);

	virtual void OnBeginCollision(Collider* src, Collider* dest) override;
	virtual void OnColliding(Collider* src, Collider* dest) override;
	virtual void OnEndCollision(Collider* src, Collider* dest) override;

	PlayerState CheckOverlap(RECT& other, RECT& intersect);

	void Serialize(BYTE data[], size_t len);
	void TickGravity();
	void TickState();
	void TickStep();


	PlayerState GetState();
	bool SetState(PlayerState st);
	bool SetLocal(bool flag);
	bool isLocal();
	bool SetJumping(bool flag);
	bool IsJumping();
	virtual void SetLeft(bool flag) override;
	bool SendDataToServer();
	int32 GetDirection();

private:
	void UpdateState();
	bool CanGo(int32 cellX, int32 cellY, vector<vector<Tile>>& tiles);
	void StopX();
	void StopY();
	void Run(int32 dir);
	void Jump();
	void DoubleJump();
	void Hit();
	void Drag();
	
	void SlowMove(int _dir);


private:
	
	int32 _dir = 1;
	int32 _gravity = 1;
	bool  _isLocal = false;
	bool  _jumping = false;
	Vec2Int _v{ 0,0 };

	PlayerState _state = PlayerState::Fall;
	vector<Flipbook*> _fbs;
	
};

