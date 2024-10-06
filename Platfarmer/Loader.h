#pragma once
#include "ResourceService.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "pch.h"

class Loader
{
public:
	virtual ~Loader() {};
	virtual void LoadImage(const wstring& path, wstring key) ;
	virtual void LoadTilemap(const wstring& path, wstring key) ;
	virtual Image* FindImage(wstring key);
	virtual Tilemap* FindTilemap(wstring key);

	Sprite* CreateSprite(wstring key, int32 x, int32 y, int32 w, int32 h);
	Flipbook* CreateFlipbook(wstring key, int32 line, int32 start, int32 end, Vec2Int size);

	Sprite* FindSprite(wstring key);
	Flipbook* FindFlipbook(wstring key);
	
private:
	unordered_map<wstring, Image*> _images;
	unordered_map<wstring, Sprite*> _sprites;
	unordered_map<wstring, Flipbook*> _flipbooks;
	unordered_map<wstring, Tilemap*> _tilemaps;
};

