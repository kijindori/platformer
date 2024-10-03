#pragma once

class Actor
{
public:
	Actor();
	virtual ~Actor();

public:
	virtual void Init()=0;
	virtual void Update()=0;
	virtual void Render(Gdiplus::Graphics* g)=0;


	Vec2Int GetPos();
	void SetPos(Vec2Int pos);
	Vec2Int GetSize();
	void SetSize(Vec2Int size);
	int32 GetLayer();
	void SetLayer(int32 layer);

private:
	Vec2Int _pos;
	Vec2Int _size{64,64};
	int32 _layer = 0;
};

