#include "pch.h"
#include "FlipbookActor.h"

FlipbookActor::FlipbookActor(Flipbook* fb): _fb(fb) 
{
	assert(fb);
}
FlipbookActor::~FlipbookActor() {}


void FlipbookActor::Init()
{
	
}


void FlipbookActor::Update()
{
	_index = (_index + 1) % (_fb->_end - _fb->_start + 1);
}

void FlipbookActor::Render(Gdiplus::Graphics* g)
{
	Vec2Int size = GetSize();
	Vec2Int pos = GetPos();
	int32 w = _fb->_size.x;
	int32 h = _fb->_size.y;
	Rect drawRect(pos.x, pos.y, size.x, size.y);
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

void FlipbookActor::SetFlipbook(Flipbook* fb)
{
	_fb = fb;
	_index = 0;
}

