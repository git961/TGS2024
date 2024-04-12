#pragma once
#include "GameMainScene.h"
class GameMainScene;

class Camera
{
private:
	float x, y;
public:
	
	Camera();
	~Camera();
	void UpdateCamera(GameMainScene* gamemain);

	void CameraSetLocation(float set_x,float set_y);

	float GetCameraX() { return x; };
	float GetCameraY() { return y; };
};

