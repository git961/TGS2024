#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
#include "StageBlock.h"
#include "AnimScene.h"
#include "padinput.h"

class GameMainScene;
class StageBlock;
class AnimScene;

enum PlayerState {
    NOMAL,//地面に居る：歩くのが可能
    ATTACK,
    WALK,
    HITDAMAGE,
    DYNAMITE,
    DEATH,
    PANIM,
    ASE
};

class Player :
    public CharacterBase
{
private:
    Input input;
    PlayerState player_state;

    int player_img[10];
    int player_walk_img[10];
    int player_attack_img[15];
    int player_throw_img[15];
    int player_death_img[15];
    int pickaxe_img[15];
    int soil_effect[10];

    int player_ase_img[10];



    float img_down;//画像の表示位置を下げる用
    int p_imgnum;//プレイヤーの画像番号切り替え用
    int p_nomal_num;

    int p_atk_imgnum;//攻撃画像切り替え用

    int walk_num;//プレイヤ歩行画像切り替え用
    int walk_abs;//プレイヤ歩行画像切りかえ計算用
    float old_worldx;

    int effect_num;//effectの画像番号切り替え用
    int anim_cnt;//画像切り替え用
    bool is_hit_enemy;//エネミーに当たったか

    int reset_timer;//攻撃をしばらくしなかった場合元に戻す

    int img_time;//画像切替の時間調節用

    float atk_cnt_timer;//攻撃発生してからとめるまでの時間をカウントする用
    int next_attackflg;//攻撃中もう一度ボタンが押されたら攻撃をする
    int attack_cnt;//何回攻撃ボタンを押したかカウント用
    int wait_atk_cnt;//もう一度攻撃できるようになるまでの時間カウント用
    bool wait_flg;//

    bool is_atk_putout;//攻撃判定を出すか？

    int atk_sound;//つるはし攻撃音
    int op_run_sound;//オープニング走る音
    int damage_sound;//被ダメージ音
    int throw_dynamite_sound;//ダイナマイト投げる音
    int death_sound;//死亡音


    //プレイヤーの状態
    bool walk;//true:歩いてる false:止まってる
    bool attacking;//true:攻撃中 false:攻撃してない 

    //ダイナマイト投擲用

    int dyna_anmcnt;//ダイナマイト投擲アニメーション切り替え用
    int dyna_throw_num;
    bool dyna_anm_start;
    bool atk_dynamite;//true:発射する false:発射してない 
    
    int dyna_stock_num;//残弾数
    int dyna_stock_cnt;//残弾補充のカウント


    //ダメージ受けた時に点滅させるよう
    bool hit_damage;//ダメージを受けた
    bool hit_cnt;//
    bool flash_start;
    bool flash_flg;//点滅させるフラグ
    int flash_cnt;

    float walk_velocity_x;

   //死亡アニメーション
    int death_anim_cnt;
    int death_num;
    bool death_flg;//死んだよフラグ


    int op_num;
    int op_cnt;

    bool tuto_anim_flg;
    int tuto_num;
    bool tuto_atk_flg;//つるはしのチュートリアル用フラグ
    int tuto_ui_num;//表示するUI
    bool rock_break_flg;
    int rock_cnt;
    int tuto_cnt;
    bool walk_stop_flg;
    bool tuto_anim_dynaflg;//カメラをダイナマイトに追従させる用
    bool start_flg;

    bool helmet_flg;//ヘルメットを落とすフラグ
    float helmet_down;
    int helmet_img;//

public:
    Player();
    ~Player();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    //プレイヤー移動用
    void PlayerMove();

    void PlayerAttack();

    bool GetAttacking() { return is_atk_putout; }
    
    bool GetAtkDynamite() { return atk_dynamite; }
    void SetAtkDynamite(bool set_flg) { atk_dynamite=set_flg; }
    int GetDynaNum() { return dyna_stock_num; }

    float GetHp() { return hp; }

    bool GetDeathFlg() { return death_flg; }



    void SetLocationY(float set_y) {
        location.y = set_y;
    }

    void SetEnemyHit(bool set_hitflg)
    {
        is_hit_enemy = set_hitflg;
    }

    void SetDamage(float damage) { hp = hp - damage; }

    void SetDamageFlg(bool set_damageflg) { hit_damage = set_damageflg; }

    void SetX(float set_x) {
        // 端に来たら跳ね返る
        if (world.x + width / 2 > set_x)
        {
            world.x = set_x - 64;

        }
    }

    

    void OpAnimUpdate(AnimScene *anim_scene,int set_case);//最初のアニメーション用
    void TutorialAnimUpdate();//チュートリアル用アップデート

    int GetTutoUiNum() { return tuto_ui_num; }
    void SetMoveStop(bool set_flg) { walk_stop_flg = set_flg; }
    bool GetTutoAnimDynaFlg() { return tuto_anim_dynaflg; }
    bool GetStartFlg() { return start_flg; }

};
