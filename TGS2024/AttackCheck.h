#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
class GameMainScene;
class Player;


class AttackCheck :
    public CharacterBase
{
private:
    Input input;

    bool attack_flg;
    float shift_x;//プレイヤーからもらったx座標をずらす用
    float shift_y;//プレイヤーからもらったy座標をずらす用

public:
    AttackCheck(class GameMainScene* set_gamemain) :CharacterBase(set_gamemain) {};
    //AttackCheck();
    ~AttackCheck();

    void Update();
    void Draw() const;
    void Initialize(float set_x, float set_y);
    void DeathAnimation();
    void Finalize();
    void Death();
    void Move();                                // 移動処理

    bool GetAttackFlg() { return attack_flg; };

};

