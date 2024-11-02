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

