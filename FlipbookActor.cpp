#include "pch.h"
#include "FlipbookActor.h"

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
	_index = (_index + 1) % (_fb->_end - _fb->_start + 1);
}

void FlipbookActor::Render(Gdiplus::Graphics* g)
{
	Super::Render(g);

	Vec2Int size = GetSize();
	Vec2Int pos = GetPos();
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

void FlipbookActor::OnBeginOverlapped(Collider* src, Collider* dest)
{
}

void FlipbookActor::OnOverlapping(Collider* src, Collider* dest)
{
}

void FlipbookActor::OnEndOverlapped(Collider* src, Collider* dest)
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

