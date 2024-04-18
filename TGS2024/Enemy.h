#pragma once
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

    int enemy_walk_img[3];      // エネミー歩行画像
    int enemy_death_img[6];      // エネミー死亡画像

    int death_cnt;  // 死亡アニメーションが終わるまでの時間
    bool is_delete;     // 削除するか？

    //int image;          // 現在の表示画像
    int anim_cnt;       // アニメーション用カウント
    bool decrease;      // アニメーション用カウント減少フラグ
    int image_num;       // 表示する画像番号

public:
    Enemy(float set_x);
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Damege(int damege);                // 被ダメージ処理

    float GetHp() { return hp; }            // hp取得
    bool GetDeleteFlg() { return is_delete; } // 削除フラグの取得
};

