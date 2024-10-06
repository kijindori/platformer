#pragma once
class Sprite
{
public:
	Sprite(Gdiplus::Image* img, int32 x, int32 y, int32 w, int32 h) :_image(img), _x(x), _y(y), _w(w), _h(h)
	{}
	Image* _image = nullptr;
	int32 _x = 0;
	int32 _y = 0;
	int32 _w = 0;
	int32 _h = 0;
};

class Flipbook
{
public:
	Flipbook(Image* img, int32 x, int32 y, int32 z, Vec2Int size) :_image(img), _line(x), _start(y), _end(z), _size(size)
	{}
	Image* _image = nullptr;
	int32 _line = 0;
	int32 _start = 0;
	int32 _end = 0;
	Vec2Int _size{ 32,32 };
};