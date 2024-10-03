#include "pch.h"
#include "SpriteActor.h"



SpriteActor::SpriteActor(Image* image): _image(image)
{
	
}
SpriteActor::~SpriteActor() {}


void SpriteActor::Init()
{

}


void SpriteActor::Update()
{

}



void SpriteActor::Render(Gdiplus::Graphics* g)
{
	Vec2Int size = GetSize();
	Vec2Int pos = GetPos();
	g->DrawImage(_image, pos.x, pos.y, 0, 0, size.x, size.y, UnitPixel );
}


