#include "pch.h"
#include "TilemapService.h"


void TilemapService::LoadFile(const wstring& path, wstring key)
{
	Tilemap* tm = new Tilemap();
	tm->LoadFile(path);
	_loader.insert(make_pair(key, tm));
}

void TilemapService::SaveFile(const wstring& path, wstring key)
{

}

void* TilemapService::Find(wstring key)
{
	assert(_loader[key]);
	return _loader[key];
}
