#include "pch.h"
#include "Player.h"
#include "Locator.h"
#include "Barrel.h"
#include "Cactus.h"

Player::Player(Flipbook* fb, Vec2Int pos): Super(fb)
{
	/*
		플레이어 생성,
		Size : 48X48 
		각 상태 별 애니메이션을 가져오고,
		충돌체를 추가합니다.
	*/

	SetSize(Vec2Int{ 48,48 });
	SetPos(pos);

	_fbs.resize((int32)PlayerState::End);

	_fbs[(int32)PlayerState::Idle]			= Locator::GetLoader()->FindFlipbook(L"Idle.png");
	_fbs[(int32)PlayerState::Ready]			= Locator::GetLoader()->FindFlipbook(L"Idle.png");
	_fbs[(int32)PlayerState::Run]			= Locator::GetLoader()->FindFlipbook(L"Run.png");
	_fbs[(int32)PlayerState::Jump]			= Locator::GetLoader()->FindFlipbook(L"Jump.png");
	_fbs[(int32)PlayerState::DoubleJump]	= Locator::GetLoader()->FindFlipbook(L"Double_Jump.png");
	_fbs[(int32)PlayerState::WallJump]		= Locator::GetLoader()->FindFlipbook(L"Wall_Jump.png");
	_fbs[(int32)PlayerState::Hit]			= Locator::GetLoader()->FindFlipbook(L"Hit.png");
	_fbs[(int32)PlayerState::Fall]			= Locator::GetLoader()->FindFlipbook(L"Fall.png");

	Collider* coll = new Collider();
	Vec2Int size = GetSize();
	coll->SetSize(Vec2Int{ size.x-30 , size.y-10});
	coll->SetRelativePos(Vec2Int(0, -1));
	
	AddComponent(coll);
}

Player::~Player() 
{

}


void Player::Init()
{
	Super::Init();
}


void Player::Update()
{
	/* Update Player State */
	UpdateState();

	TickState();

	TickGravity();

	/* Update Player Position */
	TickStep();

	/* Update Component */
	Super::Update();
}



void Player::Render(Gdiplus::Graphics* g)
{
	Super::Render(g);
}

void Player::RenderIndicator(Graphics* g)
{
	Vec2Int pos = GetPos();
	Vec2Int size = GetSize();

	// 카메라를 기준점으로 한 상대 위치로 조정
	Locator::GetCamera()->AdjustActorPosition(&pos);
	// offset
	
	int32 r = 10;
	int32 offset = r / 2;

	SolidBrush brush(Color(255, 255, 255, 255));				   // (Alpha, Red, Green, Blue)
	Pen skyBluePen(Color(255, 33, 255, 33));
	Rect rectangle(pos.x - offset, pos.y - size.y - offset, r, r); // (왼쪽, 위, 너비, 높이)

	g->FillEllipse(&brush, rectangle);
	g->DrawEllipse(&skyBluePen, rectangle);
}

void Player::OnBeginCollision(Collider* src, Collider* dest)
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
		if (dynamic_cast<Barrel*>(dest->GetOwner()))
		{
			SetState(PlayerState::DoubleJump);
			
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
void Player::OnColliding(Collider* src, Collider* dest)
{
	
	if (dynamic_cast<Cactus*>(dest->GetOwner()))
	{
		if (_state != PlayerState::Hit && _state != PlayerState::DoubleJump)
		{
			SetState(PlayerState::Hit);
		}
	}
}

void Player::OnEndCollision(Collider* src, Collider* dest)
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


void Player::Serialize(BYTE data[], size_t len)
{
	PlayerData temp;
	temp.id			= GetId();
	temp.x			= GetPos().x;
	temp.y			= GetPos().y;
	temp.state		= (uint32)GetState();
	temp.index		= GetIndex();
	temp.direction  = GetDirection();
	
	::memcpy_s(data, len, &temp, sizeof(temp));
}


PlayerState Player::GetState()
{
	return _state;
}


bool Player::SetState(PlayerState st)
{
	if (st == _state || _fbs[(int32)st] == nullptr)
		return false;


	Super::SetIndex(0);
	if (_fbs[(int32)st] != nullptr)
		Super::SetFlipbook(_fbs[(int32)st]);

	_state = st;
	if(isLocal())
		SendDataToServer();

	return true;
}

bool Player::SetLocal(bool flag)
{
	_isLocal = flag;
	return true;
}

bool Player::isLocal()
{
	return _isLocal;
}

bool Player::IsJumping()
{
	return _jumping;
}

bool Player::SetJumping(bool flag)
{
	_jumping = flag;
	return true;
}

void Player::SetLeft(bool flag)
{	
	Super::SetLeft(flag);
	_dir = flag ? -1 : 1;

	if(isLocal())
		SendDataToServer();
}


bool Player::SendDataToServer()
{
	Sleep(1);

	Session* session = Locator::GetSession();
	BYTE data[sizeof(PlayerData)];
	Serialize(data, sizeof(data));

	session->Send(data, sizeof(data));

	return true;
}

int32 Player::GetDirection()
{
	return _dir;
}


void Player::UpdateState()
{
	if (!isLocal())
		return;

	double timer;

	if (Locator::GetInputService()->IsKeyDown(KeyType::Right)) {
		// Turn Right
		SetLeft(false);
	}

	if (Locator::GetInputService()->IsKeyDown(KeyType::Left)) {
		// Turn Left
		SetLeft(true);
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
			SetState(PlayerState::Run);
			break;
		}


		if (Locator::GetInputService()->IsKeyPressed(KeyType::W))
		{
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
			SetState(PlayerState::Jump);
			break;
		}
		
		break;

	case(PlayerState::Jump):
		if (_v.y > 0)
		{
			SetState(PlayerState::Fall);
		}
		break;
	
	case(PlayerState::DoubleJump):

		if (Locator::GetInputService()->IsKeyPressed(KeyType::Right)
			|| Locator::GetInputService()->IsKeyPressed(KeyType::Left)
			)
		{
			//SlowMove(_dir);
		}
		break;

	case(PlayerState::OnGround):
		
		SetState(PlayerState::Ready);
		break;

	case(PlayerState::Hit):
		
		break;

	case(PlayerState::Fall):
		;
	}
}

void Player::SlowMove(int _dir)
{
	if(abs(_v.x) < 5)
		_v.x += _dir;
}

bool Player::CanGo(int32 cellX, int32 cellY, vector<vector<Tile>>& tiles)
{
	
	if (tiles[cellY][cellX].value == 1)
		return false;
	
	return true;
}

void Player::Jump()
{
	SetJumping(true);
	_v.y = -13;
}

void Player::DoubleJump()
{
	SetJumping(true);
	_v.x += _dir;
	_v.y = -17;
}

void Player::Hit()
{
	_v.x = _dir * -1;
	_v.y = -3;
}

void Player::Drag()
{
	if (_v.x < 0)
		_v.x = min(0, _v.x + 1);
	else
		_v.x = max(0, _v.x - 1);
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
	// 캐릭터의 방향과 진행중인 방향이 다르면 멈춥니다.
	if (_v.x * dir < 0)
	{
		StopX();
		return;
	}
		
	
	_v.x += dir * 2;
	_v.x = (_v.x < -5)	? -5 : _v.x;
	_v.x = (_v.x > 5)	?  5 : _v.x;
}

void Player::TickGravity()
{
	if (_v.y < 11)
		_v.y = min(11, _v.y + _gravity);
}

void Player::TickState()
{
	double timer = 0;

	switch (_state)
	{
	case(PlayerState::Idle):
		StopX();
		break;

	case(PlayerState::Run):
		Run(_dir);
		break;

	case(PlayerState::Hit):
		timer = GetHitTimer();
		if (timer < 1)
			Hit();
		/* 1.3초간 Hit 상태 유지 */
		if (timer > 1300)
		{
			SetHitTimer(0);
			SetState(PlayerState::Ready);
		}
		else
			/* TICK */
			SetHitTimer(timer + Locator::GetTimer()->GetInterval());
		break;

	case(PlayerState::Ready):
		SetJumping(false);
		break;

	case(PlayerState::DoubleJump):
		if (!IsJumping())
			DoubleJump();
		break;

	case(PlayerState::Jump):
		if(!IsJumping())
			Jump();
		break;

	case(PlayerState::Fall):
		if (IsJumping())
			SetJumping(false);
		break;

	}

}

/* 
	Player의 충돌체를 기준으로 다음 스텝을 진행하고 벽에 부딪히는지 확인합니다. 
	벽에 부딪힌다면 다음 스텝을 진행하지 않습니다.
	X축과 Y축을 나누어서 고려합니다.
*/
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
		StopX();
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
			SetState(PlayerState::Ready);
			break;

		case(PlayerState::DoubleJump):
			StopY();
			SetState(PlayerState::Ready);
			break;
		}

		if (_v.y > 0)
		{
			pos.y = nextCellY * tileSize.y - 1;
			Drag();
		}
			
	}

	SetPos(pos);
}
