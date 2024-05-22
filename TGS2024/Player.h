#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
#include "StageBlock.h"
#include "padinput.h"

class GameMainScene;
class StageBlock;

enum PlayerState {
    NOMAL,//地面に居る：歩くのが可能
    ATTACK,
    WALK,
    HITDAMAGE,
    DYNAMITE,
    DEATH
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


    int color13;


    
    int p_imgnum;//プレイヤーの画像番号切り替え用

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

    //プレイヤーの状態
    bool walk;//true:歩いてる false:止まってる
    bool attacking;//true:攻撃中 false:攻撃してない 

    //ダイナマイト投擲用

    int dyna_anmcnt;//ダイナマイト投擲アニメーション切り替え用
    int dyna_throw_num;
    bool dyna_anm_start;
    bool atk_dynamite;//true:発射する false:発射してない 


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

    float GetHp() { return hp; }

    bool GetDeathFlg() { return death_flg; }

    void SetGroundFlg(bool set_flg) {
        ground_flg = set_flg;
    }

    void SetLocationY(float set_y) {
        location.y = set_y;
    }

    void SetEnemyHit(bool set_hitflg)
    {
        is_hit_enemy = set_hitflg;
    }

    void SetDamage(float damage) { hp = hp - damage; }

    void SetDamageFlg(bool set_damageflg) { hit_damage = set_damageflg; }

};

//void Player::AttackPickaxe()
//{
//    if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE)
//    {
//        //Yおしたら攻撃
//    }
//}
