#include "pch.h"
#include "ImageService.h"

void ImageService::LoadFile(const wstring& path, wstring key)
{
	Image* img = new Image(path.c_str());
	_images.insert(make_pair(key, img));
}

void ImageService::SaveFile(const wstring& path, wstring key)
{

}

void* ImageService::Find(wstring key)
{
	return _images[key];
}

Sprite* ImageService::CreateSprite(wstring key, int32 x, int32 y, int32 w, int32 h)
{
	Image* img = (Image*) Find(key);
	Sprite* spr = new Sprite{ img, x, y, w, h };

	_sprites.insert(make_pair(key, spr));

	return spr;
}

Flipbook* ImageService::CreateFlipbook(wstring key, int32 line, int32 start, int32 end, Vec2Int size)
{
	Image* img = (Image*)Find(key);
	Flipbook* flipbook = new Flipbook{ img, line, start, end, size };

	_flipbooks.insert(make_pair(key, flipbook));

	return flipbook;
}

Sprite* ImageService::FindSprite(wstring key)
{
	return _sprites[key];
}


Flipbook* ImageService::FindFlipbook(wstring key)
{
	return _flipbooks[key];
}
