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
    AttackCheck();
    ~AttackCheck();

    void Update(GameMainScene* gamemain)override;
    void Draw() const override;
    void HitReaction(ObjectType set_type) override;

    bool GetAttackFlg() { return attack_flg; };

};

