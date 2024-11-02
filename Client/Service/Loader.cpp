#include "pch.h"
#include "Loader.h"

void Loader::LoadImage(const wstring& path, wstring key)
{
	Image* img = new Image(path.c_str());
	_images.insert(make_pair(key, img));
}

void Loader::LoadTilemap(const wstring& path, wstring key)
{
	Tilemap* tm = new Tilemap();
	tm->LoadFile(path);

	_tilemaps.insert(make_pair(key, tm));
}



Image* Loader::FindImage(wstring key)
{
	return _images[key];
}

Tilemap* Loader::FindTilemap(wstring key)
{
	return _tilemaps[key];
}

Sprite* Loader::CreateSprite(wstring key, int32 x, int32 y, int32 w, int32 h)
{
	Image* img = FindImage(key);
	Sprite* spr = new Sprite{ img, x, y, w, h };

	_sprites.insert(make_pair(key, spr));

	return spr;
}

Flipbook* Loader::CreateFlipbook(wstring key, int32 line, int32 start, int32 end, Vec2Int size)
{
	Image* img = FindImage(key);
	Flipbook* flipbook = new Flipbook{ img, line, start, end, size };

	_flipbooks.insert(make_pair(key, flipbook));

	return flipbook;
}

Sprite* Loader::FindSprite(wstring key)
{
	return _sprites[key];
}


Flipbook* Loader::FindFlipbook(wstring key)
{
	return _flipbooks[key];
}
