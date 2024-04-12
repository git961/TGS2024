#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "AttackCheck.h"
#include "fps.h"

class Player;
class Enemy;
class AttackCheck;

class GameMainScene :
    public AbstractScene
{
private:

    Player *player;
    Enemy *enemy;
    AttackCheck *ac;
    fps fp;

    bool enemy_damage_once;
    bool checkhit;

    float camera_x;
    float camera_y;

public:
    GameMainScene();
    ~GameMainScene();

    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;


    void UpdateCamera();

    void CameraSetLocation(float set_x, float set_y);

    float GetCameraX() { return camera_x; };
    float GetCameraY() { return camera_y; };
};

