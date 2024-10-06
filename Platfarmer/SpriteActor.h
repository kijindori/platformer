#pragma once
#include "Actor.h"
#include "pch.h"

class SpriteActor : public Actor
{
public:
	SpriteActor(Image* image);
	virtual ~SpriteActor();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Graphics* g) override;

	void SetImage(Image* image);

private:
	Image* _image = nullptr;
};

