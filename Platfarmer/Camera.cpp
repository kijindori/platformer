#include "Camera.h"

Camera::Camera(Player* actor) : _focus(actor)
{
}

Camera::~Camera()
{
}


/* 카메라를 중앙으로 한 상대 좌표로 변환 */
void Camera::AdjustActorPosition(Vec2Int* pos)
{
	Vec2Int cam = GetPos();
	pos->x += CLIENT_WIDTH / 2 - cam.x;
	pos->y += CLIENT_HEIGHT / 2 - cam.y;

	return;
}	

Vec2Int Camera::GetPos()
{
    return _pos;
}

void Camera::SetPos(Vec2Int pos)
{
	_pos = pos;
}


void Camera::UpdatePos()
{
	Vec2Int pos = _focus->GetPos();
	int32 camX = pos.x;
	int32 camY = pos.y;

	camX = std::clamp(camX, CLIENT_WIDTH / 2, 1920 - CLIENT_WIDTH / 2);
	camY = std::clamp(camY, CLIENT_HEIGHT / 2, 1024 - CLIENT_HEIGHT / 2);


	_pos = Vec2Int(camX, camY);
		
}

Player* Camera::GetFocusedPlayer()
{
	return _focus;
}

void Camera::SetFocusedPlayer(Player* focus)
{
	_focus = focus;
}
