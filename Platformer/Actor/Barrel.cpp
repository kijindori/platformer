#include "Barrel.h"
#include "Locator.h"

Barrel::Barrel(Flipbook* fb) : FlipbookActor(fb)
{
	/*
		Barrel 몬스터가 생성될 때,
		각 상태 별 애니메이션을 가져오고,
		Collider 를 추가합니다.
	*/

	_fbs.resize((int32)BarrelState::End);
	_fbs[(int32)BarrelState::Idle] = Locator::GetLoader()->FindFlipbook(L"E3_Idle.png");
	_fbs[(int32)BarrelState::Walk] = Locator::GetLoader()->FindFlipbook(L"E3_Walk.png");
	_fbs[(int32)BarrelState::Charge] = Locator::GetLoader()->FindFlipbook(L"E3_Charge.png");
	_fbs[(int32)BarrelState::Hit] = Locator::GetLoader()->FindFlipbook(L"E3_Hit.png");
	_fbs[(int32)BarrelState::Stun] = Locator::GetLoader()->FindFlipbook(L"E3_Stun.png");

	Collider* coll = new Collider();
	Vec2Int size = GetSize();
	coll->SetSize(Vec2Int{ size.x, size.y });
	AddComponent(coll);
}

Barrel::~Barrel()
{
}

void Barrel::Init()
{
	Super::Init();
}


void Barrel::Update()
{
	Super::Update();
}

void Barrel::Render(Graphics* g)
{
	Super::Render(g);
}

void Barrel::Hit()
{

}
