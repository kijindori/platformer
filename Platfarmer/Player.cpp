#include "pch.h"
#include "Player.h"
#include "Locator.h"

Player::Player(Flipbook* fb): Super(fb)
{
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
	coll->SetSize(Vec2Int{ 32, 32 });
	AddComponent(coll);
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
		myPosition.y -= h;
		break;

	case(PlayerState::UnderGround):
		myPosition.y += h;
		break;

	case(PlayerState::LeftGround):
		myPosition.x -= w;
		break;

	case(PlayerState::RightGround):
		myPosition.x += w;
		break;
	}



	SetPos(myPosition);

	_v.x = 0;
	_v.y = 0;
	_gravity = 0;

	SetState(PlayerState::Ready);
}

// 충돌 중에 위치 조정
void Player::OnOverlapping(Collider* src, Collider* dest)
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
		myPosition.y -= h;
		break;

	case(PlayerState::UnderGround):
		myPosition.y += h;
		break;

	case(PlayerState::LeftGround):
		myPosition.x -= w;
		break;

	case(PlayerState::RightGround):
		myPosition.x += w;
		break;
	}

	

	SetPos(myPosition);

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

	if (Locator::GetInputService()->IsKeyDown(KeyType::Right)) {
		Super::SetLeft(false);
		_dir = 1;
	}

	if (Locator::GetInputService()->IsKeyPressed(KeyType::Left)) {
		Super::SetLeft(true);
		_dir = -1;
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
			_v.x = 1; // run
			SetState(PlayerState::Run);
			break;
		}

		if (Locator::GetInputService()->IsKeyPressed(KeyType::W))
		{
			_v.y = -13; // jump
			_gravity = 1.5;
			SetState(PlayerState::Jump);
			break;
		}

		break;

	case(PlayerState::Run):

		if (Locator::GetInputService()->IsKeyIdle(KeyType::Right)
			&& Locator::GetInputService()->IsKeyIdle(KeyType::Left))
		{
			_v.x = 0; //stop
			SetState(PlayerState::Idle);
			break;
		}

		if (Locator::GetInputService()->IsKeyPressed(KeyType::Right)
			&& Locator::GetInputService()->IsKeyPressed(KeyType::Left)
			)
		{
			_v.x = 0; //stop
			SetState(PlayerState::Idle);
			break;
		}

		if (Locator::GetInputService()->IsKeyPressed(KeyType::W))
		{
			_v.y = -17; // jump
			_gravity = 1.5;
			SetState(PlayerState::Jump);
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

	case(PlayerState::Fall):
		if (_v.y <= 0)
			SetState(PlayerState::Ready);
	}
}

bool Player::CanGo(int32 cellX, int32 cellY, vector<vector<Tile>>& tiles)
{
	
	return tiles[cellY][cellX].value != 1;
}

void Player::Stop()
{
	_v.x = 0;
	_v.y = 0;
}

void Player::Run()
{
	_v.x = 1;
}

void Player::TickGravity()
{
	if (_v.y < 13)
		_v.y = min(13, _v.y + _gravity);
}

void Player::TickStep()
{
	Vec2Int pos = GetPos();

	Tilemap* tm = Locator::GetLoader()->FindTilemap(L"lv1-col");
	auto& tiles = tm->GetTiles();
	Vec2Int msize = tm->GetMapSize();
	Vec2Int tileSize = tm->GetTileSize();

	int32 nextX = pos.x + _v.x * _dir;
	int32 nextY = pos.y + _v.y;

	int32 currentCellX = pos.x / tileSize.x;
	int32 currentCellY = pos.y / tileSize.y;
	int32 nextCellX = nextX / tileSize.x;
	int32 nextCellY = nextY / tileSize.y;

	if (CanGo(nextCellX, currentCellY, tiles))
	{
		pos.x = nextX;
	}
	else
	{

	}

	if (CanGo(currentCellX, nextCellY, tiles))
	{
		pos.y = nextY;
		if (_state != PlayerState::Fall)
			SetState(PlayerState::Fall);
	}
	else
	{
		if (_state == PlayerState::Fall)
		{
			Stop();
			SetState(PlayerState::Ready);
		}
	}

	SetPos(pos);
}
