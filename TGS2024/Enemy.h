#pragma once
#include "CharacterBase.h"
#include "GameMainScene.h"
class GameMainScene;

// 敵の種類
enum EnemyType
{
    walk,       // 歩行
    roll        // 転がり
};

class Enemy : public CharacterBase
{
private:
    int type;       // 0:歩行　1:転がり

public:
    Enemy(float set_direction, int set_type);
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Damege(int damege);                // 被ダメージ処理
};

