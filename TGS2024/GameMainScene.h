#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "AttackCheck.h"
#include "fps.h"
#include "MapIo.h"
#include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define FIELD_WIDTH 2560 //ワールド全体の幅
#define FIELD_HEIGHT 720 //ワールド全体の高さ

#define WINDOW_HALFX SCREEN_WIDTH/2
#define WINDOW_HALFY SCREEN_HEIGHT/2


class Player;
class Enemy;
class AttackCheck;
class MapIo;

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

    MapIo *mapio;

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

    void UpdateCamera(World world);




    //float GetCameraX() { return camera_x; };
    //float GetCameraY() { return camera_y; };
};

