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
#include "Gem.h"
#include "Score.h"
#include "UI.h"
#include "Dynamite.h"
#include <math.h>
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "FragileWall.h"
#include "Cage.h"
#include "CageDoor.h"
#include "Lift.h"
#include "Magma.h"
#include "FallingFloor.h"
#include "Geyser.h"
#include "Rock.h"
#include "LongLeggedEnemy.h"
#include "HardEnemy.h"
#include "ReboundEnemy.h"
#include <crtdbg.h>
#include <stdlib.h>


class RollingEnemy;
class AttackCheck;
class MapIo;
class UI;
class Dynamite;
class Gem;
class Lift;
enum class StageNum;

struct cameraposition
{
    float x;
    float y;

};

enum GameState {
    EDITOR,
    TUTORIAL,
    POSE,
    GOAL,
    RESPAWN,
    PLAY
};


enum class StageNum
{
    stage1,
    stage2
};

struct ObjectNum {
    int fragile_wall_cnt=0;
    int cage_cnt=0;
    int cage_door_cnt=0;
    int magma_cnt;
    int falling_floor_cnt;
    int geyser_cnt;
    int lift_cnt;
    int rock_cnt;
};

class GameMainScene : public AbstractScene
{
private:

    GameState game_state;
    StageNum stage_num;

    Player* player;
    Enemy* enemy[ENEMYMAXNUM];
    RollingEnemy* rolling_enemy[ROLLING_ENEMY_MAXNUM];
    AttackCheck* ac;
    Dynamite* dynamite[DYNAMITE_MAXNUM];
    fps fp;

    MapIo* mapio;
    StageBlock* stage_block[MAP_BLOCKMAX];
    Gem* walk_gem[ENEMYMAXNUM];             // 配列
    Gem* roll_gem[ROLLING_ENEMY_MAXNUM];
    Score* score;

    Lift* lift[LIFT_MAXNUM];

    UI* ui;

    FragileWall* fragile_wall[FRAGILE_WALL_MAXNUM];          // 脆い壁
    Cage* cage[CAGE_DOOR_MAXNUM];                         // 檻
    CageDoor* cage_door[CAGE_DOOR_MAXNUM];                // 檻のドア
    Magma* magma[MAGMA_MAXMUN];                       // マグマ
    FallingFloor* falling_floor[FALLING_FLOOR_MAXNUM];        // 落ちる床
    Geyser* geyser[GEYSER_MAXNUM];                     // 間欠泉
    Rock* rock[ROCK_MAXNUM];                        //岩

    ObjectNum object_num;

    LongLeggedEnemy** long_legs_enemy;  // 脚が長い敵
    HardEnemy* hard_enemy[HARD_ENEMY_MAXNUM];             // ダイナマイトでしか倒せない敵
    ReboundEnemy* rebound_enemy[REBOUND_ENEMY_MAXNUM];      // つるはし攻撃で転がる敵

    cameraposition camera_pos;

    cameraposition screen_origin_position;

    bool retry_flg;//リトライしてきたか？

    bool pose_flg;//ポーズ中か
    bool goal_flg;//ゴールしたか

    bool player_damage_once;
    bool enemy_damage_once;
    bool rock_damage_once;

    int back_img[10];//背景入れるよう
    int goal_img;//ゴールした後に表示する画像入れる用
    int death_img;//プレイヤーが死んだとき用
    float img_extrate;//画像の拡大率変更用
    int pose_img;//poseの文字を入れる

    int check_num;//blockのどこに当たったか貰うよう

    // 背景画像スクロール用
    float location_x;
    float location_y;
    float world_x;
    float world_y;

    //camera_x - 1280 / 2;
    //camera_y - 720 / 2;

    int block_count;//配置したブロックの数
    //int rock_count;
    int enemy_count;//配置した歩行エネミーの数
    int rolling_enemy_cnt;//配置したローリングエネミーの数
    int map_old_array[map_blockmax_y][map_blockmax_x] = { 0 };//配置したエネミーを消したかチェック用

    int walk_gem_score;             // 歩行エネミーの宝石スコア
    int roll_gem_score;             // 転がるエネミーの宝石スコア
    //int rock_gem_score;             //岩から出る宝石スコア

    float camera_old_x;
    World camera_resetx;//カメラの位置リセットに
    bool camera_resetflg;

    //float check_abs;//debug用

    //画面揺らす用
    int shake_cnt;
    int shake_x1;
    int shake_x2;
    bool shake_flg;

    //チュートリアル用
    bool play_start_flg;//アニメーション終

    bool clear_flg;         // クリアしたか？
    float clear_alpha;
    bool gameover_flg;         // ゲームオーバーになったか？
    int main_bgm;
    int volume;

    int p_life_num;//プレイヤーの残機数
    bool p_notback_flg;//プレイヤー戻れなくするか
    int gameover_anim_cnt;

    //円形フェードイン
    int CircleSize;
    int ScreenHandle;
    bool fadein_flg;//フェードイン開始フラグ
    float alpha;
    bool black_flg;
    bool retry_fadein_once;//リトライしてきたときに一度だけ画面を明るくするフラグ
    int fadein_sound;//
    bool fadein_snd_flg;//フェードインサウンドをならせるか？

    int start_pause_se;            // ポーズ開始音
    int unpause_se;                    // ポーズ解除音


    bool checkhit;//当たり判定当たっているかチェック用：後で消す
    int block_cnt = 0;//blockが何個作られたか
    int check_cnt = 0;
    bool checkhit_block[3] = { false };
    int block_num[3] = { 0 };


    float respawn_x;    //復活位置ｘ
    float respawn_y;    //復活位置ｙ

public:
    GameMainScene(bool set_flg);
    virtual~GameMainScene() override;

    void ResetMap();

    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;

    virtual void Finalize() override;

    void UpdateCamera(World world);

    void SetPlayerDamageOnce(bool set_flg) { player_damage_once = set_flg; }

    void ShakeCamera(bool set_true, int set_num);

    int GetPlayerLife() { return p_life_num; }
    bool GetPlayerNotBack() { return p_notback_flg; }

    MapIo* GetMapIo() { return mapio; }

    void Tutorial();

    void EnemyDamage(int enemynum,float damage);
    void PlayerDamage();
    void GemGenerate();
    void GemUpDate();
    void EnemyHitEnemy();
    void EnemyUpDate();
    void PlayerUpDate();
    void PlayerHitGem();
    void PlayerHitEnemy();
    void PickaxeHitEnemy();
    void DynamiteHitEnemy();
    void LiftUpDate();
    void PlayerHitLift();
    void LiftHitStop();
    void PlayerHitBlock();

    void SetObjectNull();//オブジェクトにNullを入れる
    

    void FragileWallUpdate();               // 脆い壁更新処理
    void DynamiteHitFragileWall();          // ダイナマイトと脆い壁の当たり判定処理
    void PlayerHitFragileWall();            // プレイヤーと脆い壁の当たり判定処理
    void PlayerHitRock();                   // プレイヤーと壊れる岩の当たり判定処理

    void CageUpdate();                      // 檻の更新処理
    void CageDoorUpdate();                  // 檻のドアの更新処理
    void PlayerHitCageDoor();               // プレイヤーと檻のドアの当たり判定
    void CheckPlayerInCage();               // プレイヤーが檻の中にいるのか調べる
    void AttackCageDoor();                  // 檻のドアへの攻撃判定

    void MagmaUpdete();                     // マグマの更新処理
    void PlayerHitMagma();                  // プレイヤーとマグマの当たり判定処理

    void FallingFloorUpdate();              // 落ちる床の更新処理
    void PlayerHitFallingFloor();           // プレイヤーと落ちる床の当たり判定
    void PickaxeHitFallingFloor();          // つるはしと落ちる床の当たり判定
    void FallingFloorHitMagma();            // 落ちる床とマグマの当たり判定

    void GeyserUpdete();                    // 間欠泉の更新処理
    void PlayerHitGeyser();                 // プレイヤーと間欠泉の当たり判定
    void PickaxeHitGeyser();                // つるはしと間欠泉の当たり判定

    void PlayerHitRespawn();                //プレイヤーとリスポーンブロックの当たり判定

    void EnemyHitRock();//エネミーと岩ブロックの当たり判定
    void DynamiteHitRock();//ダイナマイトと岩の当たり判定
    void PickaxeHitRock();//つるはしと岩ブロックの当たり判定
    void RockUpdate();//岩のアップデート

    void LongLegsEnemyUpdate();             // 脚が長い敵の更新処理
    void PlayerHitLongLegsEnemy();          // プレイヤーと脚が長い敵の当たり判定
    void PickaxeHitLongLegsEnemy();         // つるはしと脚が長い敵の当たり判定

    void HardEnemyUpdate();                 // ダイナマイトでしか倒せない敵の更新処理
    void PlayerHitHardEnemy();              // プレイヤーとダイナマイトでしか倒せない敵の当たり判定
    void DynamiteHitHardEnemy();            // つるはしとダイナマイトでしか倒せない敵の当たり判定

    void ReboundEnemyUpdate();             // つるはしで転がる敵の更新処理
    void PlayerHitReboundEnemy();          // プレイヤーとつるはしで転がる敵の当たり判定
    void PickaxeHitReboundEnemy();         // つるはしとつるはしで転がる敵の当たり判定

    bool CollisionCheck(float set_x,float set_y);
    bool CollisionCharaRight(float set_half_width,float set_half_height,World set_xy);
    bool CollisionCharaLeft(float set_half_width, float set_half_height, World set_xy);
    bool CollisionCharaTop(float set_half_width, float set_half_height, World set_xy);
    bool CollisionCharaBottom(float set_half_width, float set_half_height, float set_x,float set_y);
};

