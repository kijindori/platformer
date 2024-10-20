#include "pch.h"
#include "Player.h"
#include "Locator.h"
#include "Barrel.h"
#include "Cactus.h"

Player::Player(Flipbook* fb): Super(fb)
{
	/*
		플레이어 생성,
		Size : 48X48 
		각 상태 별 애니메이션을 가져오고,
		Collider 를 추가합니다.
	*/

	SetSize(Vec2Int{ 48,48 });

	_fbs.resize((int32)PlayerState::End);

	_fbs[(int32)PlayerState::Idle] = Locator::GetLoader()->FindFlipbook(L"Idle.png");
	_fbs[(int32)PlayerState::Ready] = Locator::GetLoader()->FindFlipbook(L"Idle.png");
	_fbs[(int32)PlayerState::Run] = Locator::GetLoader()->FindFlipbook(L"Run.png");
	_fbs[(int32)PlayerState::Jump] = Locator::GetLoader()->FindFlipbook(L"Jump.png");
	_fbs[(int32)PlayerState::DoubleJump] = Locator::GetLoader()->FindFlipbook(L"Double_Jump.png");
	_fbs[(int32)PlayerState::WallJump] = Locator::GetLoader()->FindFlipbook(L"Wall_Jump.png");
	_fbs[(int32)PlayerState::Hit] = Locator::GetLoader()->FindFlipbook(L"Hit.png");
	_fbs[(int32)PlayerState::Fall] = Locator::GetLoader()->FindFlipbook(L"Fall.png");

	Collider* coll = new Collider();
	Vec2Int size = GetSize();
	coll->SetSize(Vec2Int{ size.x-30 , size.y-10});
	coll->SetRelativePos(Vec2Int(0, -1));
	AddComponent(coll);

	SetState(PlayerState::Fall);
}
Player::~Player() {}


void Player::Init()
{
	Super::Init();

	
}


void Player::Update()
{
	/* Update Player State */
	UpdateState();

	/**/
	TickGravity();

	/* Update Player Position */
	TickStep();

	/* Update Component  */
	Super::Update();
}



void Player::Render(Gdiplus::Graphics* g)
{
	Super::Render(g);
}

void Player::OnBeginOverlapped(Collider* src, Collider* dest)
{
	RECT intersect{};
	::IntersectRect(&intersect, src->GetRect(), dest->GetRect());

	int32 w = intersect.right - intersect.left;
	int32 h = intersect.bottom - intersect.top;

	RECT other = *dest->GetRect();
	Vec2Int myPosition = GetPos();

	PlayerState state = CheckOverlap(other, intersect);

	switch (state)
	{
	case(PlayerState::OnGround):
		if (dynamic_cast<Barrel*>(dest->GetOwner()) || dynamic_cast<Cactus*>(dest->GetOwner()))
		{
			SetState(PlayerState::DoubleJump);
			_v.y = -7;
		}
		break;

	case(PlayerState::UnderGround):
		break;

	case(PlayerState::LeftGround):
		break;

	case(PlayerState::RightGround):
		break;
	}
}

// 충돌 중에 위치 조정
void Player::OnOverlapping(Collider* src, Collider* dest)
{
	
	if (dynamic_cast<Barrel*>(dest->GetOwner()) || dynamic_cast<Cactus*>(dest->GetOwner()))
	{

		if (_state != PlayerState::Hit && _state != PlayerState::DoubleJump )
		{
			Hit();
			SetState(PlayerState::Hit);
		}

	}
}

void Player::OnEndOverlapped(Collider* src, Collider* dest)
{
	
}


PlayerState Player::CheckOverlap(RECT& other, RECT& intersect)
{
	int32 w = intersect.right - intersect.left;
	int32 h = intersect.bottom - intersect.top;


	if (w > h)
	{
		if (other.top == intersect.top)
		{
			return PlayerState::OnGround;
		}
		else
		{
			return PlayerState::UnderGround;
		}
	}
	else
	{
		if (other.left == intersect.left)
		{
			return PlayerState::LeftGround;
		}
		else
		{
			return PlayerState::RightGround;
		}
	}
}

PlayerState Player::GetState()
{
	return _state;
}


void Player::SetState(PlayerState st)
{
	if (st == _state || _fbs[(int32)st] == nullptr)
		return;


	Super::SetIndex(0);
	if (_fbs[(int32)st] != nullptr)
		Super::SetFlipbook(_fbs[(int32)st]);

	_state = st;
	
}

void Player::UpdateState()
{
	double timer;

	if (Locator::GetInputService()->IsKeyDown(KeyType::Right)) {
		// Turn Right
		_dir = 1;
		Super::SetLeft(false);
	}

	if (Locator::GetInputService()->IsKeyDown(KeyType::Left)) {
		// Turn Left
		_dir = -1;
		Super::SetLeft(true);
	}


	switch (_state)
	{
	case(PlayerState::Idle):

		if (Locator::GetInputService()->IsKeyDown(KeyType::Right)
			|| Locator::GetInputService()->IsKeyDown(KeyType::Left)
			|| Locator::GetInputService()->IsKeyDown(KeyType::W)
			)
		{
			SetState(PlayerState::Ready);
			break;
		}


		break;

	case(PlayerState::Ready):

		if (Locator::GetInputService()->IsKeyPressed(KeyType::Right)
			|| Locator::GetInputService()->IsKeyPressed(KeyType::Left)
			)
		{
			Run(_dir); 
			SetState(PlayerState::Run);
			break;
		}


		if (Locator::GetInputService()->IsKeyPressed(KeyType::W))
		{
			Jump();
			SetState(PlayerState::Jump);
			break;
		}

		break;

	case(PlayerState::Run):

		if (Locator::GetInputService()->IsKeyIdle(KeyType::Right)
			&& Locator::GetInputService()->IsKeyIdle(KeyType::Left))
		{
			StopX();
			SetState(PlayerState::Idle);
			break;
		}

		if (Locator::GetInputService()->IsKeyPressed(KeyType::Right)
			&& Locator::GetInputService()->IsKeyPressed(KeyType::Left)
			)
		{
			StopX();
			SetState(PlayerState::Idle);
			break;
		}

		if (Locator::GetInputService()->IsKeyPressed(KeyType::W))
		{
			Jump();
			SetState(PlayerState::Jump);
			break;
		}

		if (Locator::GetInputService()->IsKeyPressed(KeyType::Right)
			|| Locator::GetInputService()->IsKeyPressed(KeyType::Left))
		{
			Run(_dir);
			SetState(PlayerState::Run);
			break;
		}


		
		break;

	case(PlayerState::Jump):
		if (_v.y > 0)
			SetState(PlayerState::Fall);

		break;

	case(PlayerState::OnGround):
		SetState(PlayerState::Ready);
		break;

	case(PlayerState::Hit):
		timer = GetTimer();
		/* 1.3초간 Hit 상태 유지 */
		if (timer > 1300) // 2000 ms
		{
			SetTimer(0);
			SetState(PlayerState::Ready);
		}
		else
			/* TICK */
			SetTimer( timer + Locator::GetTimer()->GetInterval() );
		break;

	case(PlayerState::Fall):
		;
	}
}

bool Player::CanGo(int32 cellX, int32 cellY, vector<vector<Tile>>& tiles)
{
	
	if (tiles[cellY][cellX].value == 1)
		return false;
	
	return true;
}

void Player::Jump()
{
	_v.y = -13;
}

void Player::Hit()
{
	_v.x = _dir * -3.0;
	_v.y = -9;
}

void Player::Drag()
{
	if (_v.x < 0)
		_v.x = min(0, _v.x + .7);
	else
		_v.x = max(0, _v.x - .7);
}

void Player::StopX()
{
	_v.x = 0;
}

void Player::StopY()
{
	_v.y = 0;
}
void Player::Run(int32 dir)
{
	// 캐릭터의 방향과 진행 방향이 다르면 멈춥니다.
	if (_v.x * dir < 0)
	{
		StopX();
		return;
	}
		
	
	_v.x += dir * 2.0;
	_v.x = (_v.x < -5)	? -5 : _v.x;
	_v.x = (_v.x > 5)	?  5 : _v.x;
}

void Player::TickGravity()
{
	if (_v.y < 11)
		_v.y = min(11, _v.y + _gravity);
}

/* Player의 충돌체를 기준으로 다음 스텝을 진행하고 충돌하는지 확인합니다. */
void Player::TickStep()
{
	Vec2Int pos = GetCollider()->GetAbsolutePos();

	Tilemap* tm = Locator::GetLoader()->FindTilemap(L"lv1-col");
	auto& tiles = tm->GetTiles();
	Vec2Int tileSize = tm->GetTileSize();

	int32 sizeX = GetCollider()->GetSize().x;
	int32 sizeY = GetCollider()->GetSize().y;


	int32 nextX = _v.x > 0 ? pos.x + sizeX / 2 + _v.x  : pos.x - sizeX / 2 + _v.x ;
	int32 nextY = _v.y > 0 ? pos.y + _v.y : pos.y - sizeY + _v.y;

	/* 현재 위치한 셀 좌표 */
	//TODO : 식 정리
	int32 currentCellX = _dir > 0 ? (pos.x + sizeX / 2) / tileSize.x : (pos.x - sizeX/2) / tileSize.x;
	int32 currentCellXForCheckFalling = pos.x / tileSize.x;
	int32 currentCellY = _v.y > 0 ?  pos.y / tileSize.y : (pos.y - sizeY) / tileSize.y;

	/* 다음 스텝의 셀 좌표 */
	int32 nextCellX = nextX / tileSize.x;
	int32 nextCellY = nextY / tileSize.y;

	bool canGoX = CanGo(nextCellX, currentCellY, tiles);
	bool canGoY = CanGo(currentCellXForCheckFalling , nextCellY, tiles);

	/* 다음 스텝의 X축 셀 이동 가능 ? */
	if ( canGoX )
	{
		pos.x += _v.x;
	}
	else
	{
		
	}

	/* 다음 스텝의 Y축 셀 이동 가능 ? */
	if ( canGoY )
	{
		pos.y += _v.y;
	}
	else
	{
		switch (_state)
		{
		case(PlayerState::Fall):
			SetState(PlayerState::Ready);
			break;

		case(PlayerState::Jump):
			StopY();
			SetState(PlayerState::Fall);
			break;

		case(PlayerState::DoubleJump):
			StopY();
			SetState(PlayerState::Ready);
		
		}

		if (_v.y > 0)
		{
			pos.y = nextCellY * tileSize.y - 1;
			Drag();
		}
			
	}

	SetPos(pos);
}
