#include "pch.h"
#include "TilemapActor.h"

TilemapActor::TilemapActor() {}
TilemapActor::~TilemapActor() {}


void TilemapActor::Init()
{

}


void TilemapActor::Update()
{

}


void TilemapActor::Render(Gdiplus::Graphics* g)
{
	Vec2Int mapSize = _tilemap->GetMapSize();
	Vec2Int tileSize = _tilemap->GetTileSize();

	auto& tiles = _tilemap->GetTiles();
	for (int32 y = 0; y < mapSize.y; y++) {
		for (int32 x = 0; x < mapSize.x; x++)
		{
			int32 val = tiles[y][x].value;
			int32 posX = x * tileSize.x;
			int32 posY = y * tileSize.y;
			Gdiplus::Rect drawRect(posX, posY, tileSize.x, tileSize.y);

			if (val)
			{
				//g->DrawImage(wallTexture, drawRect, val * tileSize.x, 0, tileSize.x, tileSize.y, UnitPixel);
			}
		}
	}
}
