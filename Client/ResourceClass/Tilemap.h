#pragma once
#include <iostream>
#include <fstream>

struct Tile
{
	int value = 0;
};

class Tilemap
{
public:
	void SetMapSize(int32 x, int32 y);
	Vec2Int GetMapSize();

	void SetTileSize(int32 x, int32 y);
	Vec2Int GetTileSize();

	vector<vector<Tile>>& GetTiles();

	vector<vector<Tile>>& Init();

	void LoadFile(const wstring& path);
	void SaveFile(const wstring& path);


private:
	Vec2Int _mapSize{60,32};
	Vec2Int _tileSize{ 32,32 };
	vector<vector<Tile>> _tm;
};

