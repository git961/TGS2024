#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"

class Player;
class Enemy;

class GameMainScene :
    public AbstractScene
{
private:

    Player *player;
    Enemy *enemy;
    bool checkhit;

public:
    GameMainScene();
    ~GameMainScene();

    void Update() override;
    void Draw() const override;
    AbstractScene* Change() override;
};

