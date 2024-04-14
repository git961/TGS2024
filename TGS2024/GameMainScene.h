#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "AttackCheck.h"
#include "fps.h"
#include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


class Player;
class Enemy;
class AttackCheck;

struct cameraposition
{
    float x;
    float y;

};

class GameMainScene :
    public AbstractScene
{
private:

    Player *player;
    Enemy *enemy;
    AttackCheck *ac;
    fps fp;

    cameraposition camera_pos;

    cameraposition screen_origin_position;

    bool enemy_damage_once;
    bool checkhit;

    int back_img;//背景入れるよう


    //camera_x - 1280 / 2;
    //camera_y - 720 / 2;


public:
    GameMainScene();
    ~GameMainScene();

    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;

    void UpdateCamera(Vec2 player_pos);




    //float GetCameraX() { return camera_x; };
    //float GetCameraY() { return camera_y; };
};

