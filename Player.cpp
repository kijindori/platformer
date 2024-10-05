#include "pch.h"
#include "Player.h"
#include "Locator.h"

Player::Player(Flipbook* fb): Super(fb)
{
	_fbs.resize((int32)PlayerState::End);

	_fbs[(int32)PlayerState::Idle] = Locator::GetImageService()->FindFlipbook(L"Idle.png");
	_fbs[(int32)PlayerState::Ready] = Locator::GetImageService()->FindFlipbook(L"Idle.png");
	_fbs[(int32)PlayerState::Run] = Locator::GetImageService()->FindFlipbook(L"Run.png");
	_fbs[(int32)PlayerState::Jump] = Locator::GetImageService()->FindFlipbook(L"Jump.png");
	_fbs[(int32)PlayerState::DoubleJump] = Locator::GetImageService()->FindFlipbook(L"Double_Jump.png");
	_fbs[(int32)PlayerState::WallJump] = Locator::GetImageService()->FindFlipbook(L"Wall_Jump.png");
	_fbs[(int32)PlayerState::Hit] = Locator::GetImageService()->FindFlipbook(L"Hit.png");
	_fbs[(int32)PlayerState::Fall] = Locator::GetImageService()->FindFlipbook(L"Fall.png");

	Collider* coll = new Collider();
	coll->SetSize(Vec2Int{ 48, 48 });
	AddComponent(coll);
}
Player::~Player() {}


void Player::Init()
{
	Super::Init();

	
}


void Player::Update()
{
	Super::Update();

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
			_v.x = 3; // run
			SetState(PlayerState::Run);
			break;
		}

		if (Locator::GetInputService()->IsKeyPressed(KeyType::W)) 
		{
			_v.y = -17; // jump
			_gravity = 3;
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
			_gravity = 3;
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

	if (_v.y > 0)
		SetState(PlayerState::Fall);

	if (_v.y < 13)
		_v.y = min(13, _v.y + _gravity);

	Vec2Int pos = GetPos();
	pos.x += _v.x * _dir;
	pos.y += _v.y;

	SetPos(pos);

}



void Player::Render(Gdiplus::Graphics* g)
{
	Super::Render(g);
}

void Player::OnBeginOverlapped(Collider* src, Collider* dest)
{
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


void Player::SetState(PlayerState st)
{
	if (st == _state || _fbs[(int32)st] == nullptr)
		return;


	Super::SetIndex(0);
	if (_fbs[(int32)st] != nullptr)
		Super::SetFlipbook(_fbs[(int32)st]);

	_state = st;
	
}
