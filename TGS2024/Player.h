#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
#include "StageBlock.h"
#include "padinput.h"

class GameMainScene;
class StageBlock;

enum PlayerState {
    NOMAL,//地面に居る：歩くのが可能
    JUMP,    //ジャンプ中：上昇だけ
    FALLING,//落下：下降だけ
    ATTACK
};

class Player :
    public CharacterBase
{
private:
    Input input;
    PlayerState player_state;

    int player_img[10];
    int player_walk_img[10];
    int player_attack_img[10];
    int pickaxe_img[10];
    int soil_effect[10];



    int p_imgnum;//プレイヤーの画像番号切り替え用
    int effect_num;//effectの画像番号切り替え用
    int anim_cnt;//画像切り替え用
    bool is_hit_enemy;//エネミーに当たったか

    float atk_cnt_timer;//攻撃発生してからとめるまでの時間をカウントする用
    int next_attackflg;//攻撃中もう一度ボタンが押されたら攻撃をする
    int attack_cnt;//何回攻撃ボタンを押したかカウント用
    int wait_atk_cnt;//もう一度攻撃できるようになるまでの時間カウント用
    bool wait_flg;//

    int atk_sound;//つるはし攻撃音

    //プレイヤーの状態
    bool walk;//true:歩いてる false:止まってる
    bool attacking;//true:攻撃中 false:攻撃してない 

    float walk_velocity_x;

       
        
    float vel;//ｙ報告の速度
    float acc;//重力加速度
    float is_jump;//ジャンプが出来る状態か？

    float fall_vel;//落下するときのｙ方向の速度
    float fall_acc;//落下するときの重力加速度

    float y_ground;//地面の高さデバック用
    float v_max;//速度最大値


public:
    Player();
    ~Player();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    //プレイヤージャンプ用
    void PlayerJump();

    //プレイヤー落下
    void PlayerFALL();

    //プレイヤー移動用
    void PlayerMove();

    bool GetAttacking() { return attacking; };

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

};

//void Player::AttackPickaxe()
//{
//    if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE)
//    {
//        //Yおしたら攻撃
//    }
//}
