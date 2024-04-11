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

    float atk_cnt_timer;//攻撃発生してからとめるまでの時間をカウントする用

       //プレイヤーの状態
        bool walk;//true:歩いてる false:止まってる
        bool attacking;//true:攻撃中 false:攻撃してない 


public:
    Player();
    ~Player();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    //プレイヤー攻撃用モーション　Pickaxe：つるはし
    void AttackPickaxe();

    bool GetAttacking() { return attacking; };
};

//void Player::AttackPickaxe()
//{
//    if (input.CheckBtn(XINPUT_BUTTON_Y) == TRUE)
//    {
//        //Yおしたら攻撃
//    }
//}
