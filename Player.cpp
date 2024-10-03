#include "pch.h"
#include "Player.h"
#include "Locator.h"

Player::Player(Flipbook* fb): Super(fb)
{
	_fbs.resize((int32)PlayerState::End);

	_fbs[(int32)PlayerState::Idle] = Locator::GetImageService()->FindFlipbook(L"Idle.png");
	_fbs[(int32)PlayerState::Run] = Locator::GetImageService()->FindFlipbook(L"Run.png");
	_fbs[(int32)PlayerState::Jump] = Locator::GetImageService()->FindFlipbook(L"Jump.png");
	_fbs[(int32)PlayerState::DoubleJump] = Locator::GetImageService()->FindFlipbook(L"Double_Jump.png");
	_fbs[(int32)PlayerState::WallJump] = Locator::GetImageService()->FindFlipbook(L"Wall_Jump.png");
	_fbs[(int32)PlayerState::Hit] = Locator::GetImageService()->FindFlipbook(L"Hit.png");
	_fbs[(int32)PlayerState::Fall] = Locator::GetImageService()->FindFlipbook(L"Fall.png");
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
		_dir = 1;
	}

	if (Locator::GetInputService()->IsKeyPressed(KeyType::Left)) {
		_dir = -1;
	}


	switch (_state)
	{
	case(PlayerState::Idle):

		if (Locator::GetInputService()->IsKeyDown(KeyType::Right)
			|| Locator::GetInputService()->IsKeyDown(KeyType::Left)
			) {
			SetState(PlayerState::Run);
			break;
		}

		if (Locator::GetInputService()->IsKeyDown(KeyType::W)) {
			SetState(PlayerState::Jump);
			break;
		}

		_v.x = 0;

		break;

	case(PlayerState::Run):	

		if (Locator::GetInputService()->IsKeyIdle(KeyType::Right)
			&& Locator::GetInputService()->IsKeyIdle(KeyType::Left))
		{
			SetState(PlayerState::Idle);
			break;
		}

		_v.x = 3;

		break;

	case(PlayerState::Jump):

		break;

	}

	if (_v.y > 0)
		SetState(PlayerState::Fall);

	//if (_velocity.y < 15)
		//_velocity.y = min(15, _velocity.y + 1);

	Vec2Int pos = GetPos();
	pos.x += _v.x * _dir;
	pos.y += _v.y;

	SetPos(pos);

}



void Player::Render(Gdiplus::Graphics* g)
{
	Super::Render(g);
}

void Player::SetState(PlayerState st)
{
	
	Super::SetIndex(0);
	Super::SetFlipbook(_fbs[(int32)st]);

	_state = st;
	
}
