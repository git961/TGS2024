#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "RollingEnemy.h"
#include "AttackCheck.h"
#include "fps.h"
#include "MapIo.h"
#include "StageBlock.h"
#include <math.h>
#include "Define.h"


class Player;
class Enemy;
class RollingEnemy;
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
    RollingEnemy* rolling_enemy;
    AttackCheck *ac;
    fps fp;

    MapIo *mapio;
    StageBlock *stage_block;

    cameraposition camera_pos;

    cameraposition screen_origin_position;

    bool enemy_damage_once;
    bool checkhit;
    bool enemyhit;      // 歩行エネミー同士の当たり判定チェック用、後に削除

    int back_img;//背景入れるよう


    // 背景画像スクロール用
    // ※　後で削除予定！！！
    float location_x;
    float location_y;
    float world_x;
    float world_y;

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

