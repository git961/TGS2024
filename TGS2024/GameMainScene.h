#pragma once
#include "Define.h"
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "RollingEnemy.h"
#include "AttackCheck.h"
#include "fps.h"
#include "MapIo.h"
#include "StageBlock.h"
#include "UIHP.h"
#include "Dynamite.h"
#include <math.h>



class Player;
class Enemy;
class RollingEnemy;
class AttackCheck;
class MapIo;
class StageBlock;
class UIHP;
class Dynamite;

struct cameraposition
{
    float x;
    float y;

};

enum GameState {
    EDITOR,
    POSE,
    GOAL,
    PLAY
};

class GameMainScene :
    public AbstractScene
{
private:

    GameState game_state;

    Player* player;
    Enemy** enemy;
    RollingEnemy* rolling_enemy;
    AttackCheck* ac;
    Dynamite* dynamite;
    fps fp;

    MapIo* mapio;
    StageBlock** stage_block;

    UIHP* ui_hp;

    cameraposition camera_pos;

    cameraposition screen_origin_position;

    bool pose_flg;//ポーズ中か
    bool goal_flg;//ゴールしたか

    bool player_damage_once;
    bool enemy_damage_once;
    bool checkhit;
    //bool enemyhit;      // 歩行エネミー同士の当たり判定チェック用、後に削除

    int back_img;//背景入れるよう

    int check_num;//blockのどこに当たったか貰うよう

    // 背景画像スクロール用
    // ※　後で削除予定！！！
    float location_x;
    float location_y;
    float world_x;
    float world_y;

    //camera_x - 1280 / 2;
    //camera_y - 720 / 2;

    int block_count;//配置したブロックの数
    int enemy_count;//配置したエネミーの数
    int map_old_array[map_blockmax_y][map_blockmax_x];//配置したエネミーを消したかチェック用

    int defeat_enemy_num;           // 倒した敵の数

public:
    GameMainScene();
    ~GameMainScene();

    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;

    void UpdateCamera(World world);

    void SetPlayerDamageOnce(bool set_flg) { player_damage_once = set_flg; }


    //float GetCameraX() { return camera_x; };
    //float GetCameraY() { return camera_y; };
};

