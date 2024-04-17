﻿#pragma once
#define DEBUG		// デバッグ用、消すと#ifdef DEBUGの処理がされなくなる

#include <stdlib.h>         // スポーン位置決定用
#include <time.h>           // スポーン位置決定用
#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

class Enemy : public CharacterBase
{
private:
    //int num;        // スポーン位置設定用
    //int death_cnt;  // 死亡アニメーションが終わるまでの時間

public:
    Enemy(float set_x);
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Damege(int damege);                // 被ダメージ処理

    float GetHp() { return hp; }            // hp取得
    //int GetDeathCnt() { return death_cnt; } // 死亡アニメーション終了時間の取得
};

