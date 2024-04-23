#pragma once
#include "Define.h"
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "AttackCheck.h"
#include "fps.h"
#include "MapIo.h"
#include "StageBlock.h"
#include <math.h>



class Player;
class Enemy;
class AttackCheck;
class MapIo;
class StageBlock;

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
    Enemy **enemy;
    AttackCheck *ac;
    fps fp;

    MapIo *mapio;
    StageBlock **stage_block;

    cameraposition camera_pos;

    cameraposition screen_origin_position;

    bool enemy_damage_once;
    bool checkhit;

    int back_img;//背景入れるよう

    int check_num;//blockのどこに当たったか貰うよう


    int count;

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

