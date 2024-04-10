#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
class GameMainScene;
class Player;


class AttackCheck :
    public CharacterBase
{
private:
    CharacterBase charabase;
    Input input;

    bool attack_flg;

public:
    AttackCheck();
    ~AttackCheck();

    void Update(GameMainScene* gamemain,Player* player);
    void Draw() const;

    bool GetAttackFlg() { return attack_flg; };

};

