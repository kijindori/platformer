#pragma once

class Component;
class Collider;

class Actor
{
public:
	Actor();
	virtual ~Actor();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(Gdiplus::Graphics* g);


	Vec2Int GetPos();
	void SetPos(Vec2Int pos);
	Vec2Int GetSize();
	void SetSize(Vec2Int size);
	int32 GetLayer();
	void SetLayer(int32 layer);

	void AddComponent(Component* comp);

	virtual void OnBeginOverlapped(Collider* src, Collider* dest) = 0;
	virtual void OnOverlapping(Collider* src, Collider* dest) = 0;
	virtual void OnEndOverlapped(Collider* src, Collider* dest) = 0;

private:
	Vec2Int _pos{0,0};
	Vec2Int _size{64,64};
	int32 _layer = 0;

	vector<Component*> _comp;
};

