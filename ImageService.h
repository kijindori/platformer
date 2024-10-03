#pragma once
#include "ResourceService.h"
#include "Sprite.h"
#include "pch.h"

class ImageService : public ResourceService
{
public:
	virtual ~ImageService() {};
	virtual void LoadFile(const wstring& path, wstring key) override;
	virtual void SaveFile(const wstring& path, wstring key) override;
	virtual void* Find(wstring key);

	Sprite* CreateSprite(wstring key, int32 x, int32 y, int32 w, int32 h);
	Flipbook* CreateFlipbook(wstring key, int32 line, int32 start, int32 end, Vec2Int size);

	Sprite* FindSprite(wstring key);
	Flipbook* FindFlipbook(wstring key);
	
private:
	unordered_map<wstring, Image*> _images;
	unordered_map<wstring, Sprite*> _sprites;
	unordered_map<wstring, Flipbook*> _flipbooks;
};

