#pragma once
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
	double _duration = .57;
	double _interval = _duration / (_end - _start + 1) * 1000;
};