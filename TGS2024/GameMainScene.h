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

class Player;
class Enemy;
class RollingEnemy;
class AttackCheck;
class MapIo;
class StageBlock;
class UI;
class Dynamite;
class Gem;

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

class GameMainScene :
    public AbstractScene
{
private:

    GameState game_state;

    Player* player;
    Enemy** enemy;
    RollingEnemy** rolling_enemy;
    AttackCheck* ac;
    Dynamite** dynamite;
    fps fp;

    MapIo *mapio;
    StageBlock **stage_block;
    Gem** walk_gem;             // 配列
    Gem** roll_gem;
    Score* score;

    UI* ui;

    cameraposition camera_pos;

    cameraposition screen_origin_position;

    bool pose_flg;//ポーズ中か
    bool goal_flg;//ゴールしたか

    bool player_damage_once;
    bool enemy_damage_once;
    bool rock_damage_once;
    bool checkhit;
    //bool enemyhit;      // 歩行エネミー同士の当たり判定チェック用、後に削除

    int back_img[10];//背景入れるよう
    int goal_img;//ゴールした後に表示する画像入れる用
    int death_img;//プレイヤーが死んだとき用
    float img_extrate;//画像の拡大率変更用

    int check_num;//blockのどこに当たったか貰うよう

    // 背景画像スクロール用
    float location_x;
    float location_y;
    float world_x;
    float world_y;

    //camera_x - 1280 / 2;
    //camera_y - 720 / 2;

    int block_count;//配置したブロックの数
    int enemy_count;//配置した歩行エネミーの数
    int rolling_enemy_cnt;//配置したローリングエネミーの数
    int map_old_array[map_blockmax_y][map_blockmax_x];//配置したエネミーを消したかチェック用

    int walk_gem_score;             // 歩行エネミーの宝石スコア
    int roll_gem_score;             // 転がるエネミーの宝石スコア

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

    //円形フェードイン
    int CircleSize;
    int ScreenHandle;
    bool fadein_flg;//フェードイン開始フラグ
    float alpha;
    bool black_flg;
    int p_death_cnt;//プレイヤーが何回死んだかカウントする用

public:
    GameMainScene();
    ~GameMainScene();

    void ResetMap();

    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;

    void UpdateCamera(World world);

    void SetPlayerDamageOnce(bool set_flg) { player_damage_once = set_flg; }

    void ShakeCamera(bool set_true, int set_num);

    void Tutorial();

    //float GetCameraX() { return camera_x; };
    //float GetCameraY() { return camera_y; };
};

