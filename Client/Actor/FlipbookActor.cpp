#include "pch.h"
#include "FlipbookActor.h"
#include "Locator.h"

FlipbookActor::FlipbookActor(Flipbook* fb): _fb(fb) 
{
	assert(fb);
}
FlipbookActor::~FlipbookActor() {}


void FlipbookActor::Init()
{
	Super::Init();
}


void FlipbookActor::Update()
{
	Super::Update();
	double interval = _fb->_interval;
	double timer = GetTimer() + Locator::GetTimer()->GetInterval();
	
	if (timer > interval)
	{
		_index = (_index + 1) % (_fb->_end - _fb->_start + 1);
		timer -= interval;
	}
	SetTimer(timer);
}

void FlipbookActor::Render(Gdiplus::Graphics* g)
{
	Super::Render(g);

	Vec2Int size = GetSize();
	Vec2Int pos = GetPos();

	Locator::GetCamera()->AdjustActorPosition(&pos);
	

	int32 w = _fb->_size.x;
	int32 h = _fb->_size.y;

	Rect drawRect;
	if (_turnLeft)
	{
		drawRect = Rect(pos.x + size.x / 2, pos.y - size.y, -size.x, size.y);
	}
	else
	{
		drawRect = Rect(pos.x - size.x / 2 , pos.y - size.y , size.x, size.y);
	}
	
	g->DrawImage(
		_fb->_image,
		drawRect,
		(_fb->_start + _index) * w,
		_fb->_line * h,
		w,
		h,
		UnitPixel
	);
}

void FlipbookActor::OnBeginCollision(Collider* src, Collider* dest)
{
}

void FlipbookActor::OnColliding(Collider* src, Collider* dest)
{
}

void FlipbookActor::OnEndCollision(Collider* src, Collider* dest)
{
}



void FlipbookActor::SetLeft(bool flag)
{
	_turnLeft = flag;
}

void FlipbookActor::SetFlipbook(Flipbook* fb)
{
	_fb = fb;
	_index = 0;
}

uint32 FlipbookActor::GetIndex()
{
	return _index;
}

