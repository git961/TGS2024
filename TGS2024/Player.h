#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
#include "padinput.h"

class GameMainScene;

class Player :
    public CharacterBase
{
private:
    CharacterBase charabase;
    Input input;

    int player_walk_img[10];
    int player_attack_img[10];
    int anim_cnt;//画像切り替え用

    float atk_cnt_timer;//攻撃発生してからとめるまでの時間をカウントする用

       //プレイヤーの状態
        bool walk;//true:歩いてる false:止まってる
        bool attacking;//true:攻撃中 false:攻撃してない 

        float walk_velocity_x;


        bool jump_flg;//true:ジャンプ中　false:地面に居る
        bool jump_start_flg;//ボタンが押されたら
        
        float jump_timer;
        float rad;
        float sita;
        float pi = 3.1415f;


        float jump_v0;//ジャンプの初速度
        float gravity;//ジャンプの重力
        float velocity_y;//y方向の速度

        float y_ground;//地面の高さデバック用
        float v_max;//速度最大値


public:
    Player();
    ~Player();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    //プレイヤー攻撃用モーション　Pickaxe：つるはし
    void AttackPickaxe();

    //プレイヤージャンプ用
    void PlayerJump();

    //プレイヤー移動用
    void PlayerMove();

    bool GetAttacking() { return attacking; };
};

//void Player::AttackPickaxe()
//{
//    if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE)
//    {
//        //Yおしたら攻撃
//    }
//}
