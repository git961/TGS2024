#pragma once
#define DEBUG		// デバッグ用、消すと#ifdef DEBUGの処理がされなくなる

#include <stdlib.h>
#include <time.h>
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
    int num;        // スポーン位置設定用

public:
    Enemy(int set_type);
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Damege(int damege);                // 被ダメージ処理

    float GetHp() { return hp; }            // hp取得
};

