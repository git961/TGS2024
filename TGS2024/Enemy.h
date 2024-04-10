#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
class GameMainScene;

class Enemy :
    public CharacterBase
{
private:
public:

    Enemy();
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    float GetEnemyX() { return x; };
    float GetEnemyY() { return y; };

    float GetEnemyWidth() { return width; };
    float GetEnemyHeight() { return height; };


};

