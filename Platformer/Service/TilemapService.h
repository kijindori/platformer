#pragma once
#include "ResourceService.h"
#include "Tilemap.h"

class TilemapService : public ResourceService
{
public:
	virtual ~TilemapService() {};

	virtual void LoadFile(const wstring& path, wstring key) override;
	virtual void SaveFile(const wstring& path, wstring key) override;
	virtual void* Find(wstring key);

private:
	unordered_map<wstring, Tilemap*> _loader;
};

