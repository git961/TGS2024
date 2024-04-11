#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "AttackCheck.h"
#include "fps.h"

class Player;
class Enemy;
class AttackCheck;

class GameMainScene :
    public AbstractScene
{
private:

    Player *player;
    Enemy *enemy;
    AttackCheck *ac;
    fps fp;

    bool checkhit;

public:
    GameMainScene();
    ~GameMainScene();

    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;
};

