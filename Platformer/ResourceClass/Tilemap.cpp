#include "pch.h"
#include "Tilemap.h"

void Tilemap::SetTileSize(int32 x, int32 y)
{
	_tileSize.x = x;
	_tileSize.y = y;
}

Vec2Int Tilemap::GetTileSize()
{
	return _tileSize;
}

vector<vector<Tile>>& Tilemap::GetTiles()
{
	return _tm;
}

void Tilemap::SetMapSize(int32 x, int32 y)
{
	_mapSize.x = x;
	_mapSize.y = y;

	_tm = vector<vector<Tile>>(_mapSize.y, vector<Tile>(_mapSize.x));

}

Vec2Int Tilemap::GetMapSize()
{
	return _mapSize;
}

vector<vector<Tile>>& Tilemap::Init()
{
	_tm.resize(_mapSize.y, vector<Tile>(_mapSize.x));

	return _tm;
}

void Tilemap::LoadFile(const wstring& path)
{
	FILE* file = nullptr;

	::_wfopen_s(&file, path.c_str(), L"rb");
	assert(file);

	::fread(&_mapSize.x, sizeof(_mapSize.x), 1, file);
	::fread(&_mapSize.y, sizeof(_mapSize.y), 1, file);

	SetMapSize(_mapSize.x, _mapSize.y);

	for (int32 y = 0; y < _mapSize.y; y++)
	{
		for (int32 x = 0; x < _mapSize.x; x++)
		{
			int32 value = -1;
			::fread(&value, sizeof(value), 1, file);
			_tm[y][x].value = value;
		}
	}

	::fclose(file);
	return;
}

void Tilemap::SaveFile(const wstring& path)
{
	wofstream ofs;
	ofs.open(path);

	ofs << _mapSize.x << endl;
	ofs << _mapSize.y << endl;

	for (int32 y = 0; y < _mapSize.y; y++)
	{
		for (int32 x = 0; x < _mapSize.x; x++)
		{
			ofs << _tm[y][x].value;
		}

		ofs << endl;
	}

	ofs.close();
}



