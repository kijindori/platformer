#include "Cactus.h"
#include "Locator.h"

Cactus::Cactus(Flipbook* fb): FlipbookActor(fb)
{
	_fbs.resize((int32) CactusState::End);
	_fbs[(int32)CactusState::Idle] = Locator::GetLoader()->FindFlipbook(L"E2_Idle.png");
	_fbs[(int32)CactusState::Run] = Locator::GetLoader()->FindFlipbook(L"E2_Run.png");
	_fbs[(int32)CactusState::Fall] = Locator::GetLoader()->FindFlipbook(L"E2_Fall.png");
	_fbs[(int32)CactusState::Hit] = Locator::GetLoader()->FindFlipbook(L"E2_Hit.png");
	_fbs[(int32)CactusState::Jump] = Locator::GetLoader()->FindFlipbook(L"E2_Jump.png");

	/* 충돌체를 생성하고, 크기를 Actor 의 크기로 수정합니다. */
	Collider* coll = new Collider();
	Vec2Int size = GetSize();
	coll->SetSize(Vec2Int{ size.x, size.y });
	AddComponent(coll);
}

Cactus::~Cactus()
{
}

void Cactus::Init()
{
	Super::Init();
}


void Cactus::Update()
{
	Super::Update();
}

void Cactus::Render(Graphics* g)
{
	Super::Render(g);
}

void Cactus::Hit()
{
}
