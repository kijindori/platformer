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
	wifstream ifs;
	ifs.open(path);

	ifs >> _mapSize.x >> _mapSize.y;

	Init();

	for (int32 y = 0; y < _mapSize.y; y++)
	{
		wstring line;
		ifs >> line;

		for (int32 x = 0; x < _mapSize.x; x++)
		{
			_tm[y][x].value = line[x] - L'0';
		}
	}

	ifs.close();
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



