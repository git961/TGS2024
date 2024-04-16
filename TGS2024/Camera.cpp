#include "Camera.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720



Camera::Camera()
{
	x = 0;
	y = 0;
}

Camera::~Camera()
{
}

void Camera::UpdateCamera(GameMainScene* gamemain)
{
	//
}

void Camera::CameraSetLocation(float set_x, float set_y)
{
	x = set_x - (SCREEN_WIDTH / 2);
	y = set_y - (SCREEN_HEIGHT / 2);
}

