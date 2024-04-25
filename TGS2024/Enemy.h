#pragma once
#define DEBUG		        // デバッグ用、消すと#ifdef DEBUGの処理がされなくなる

#include <stdlib.h>         // スポーン位置決定用
#include <time.h>           // スポーン位置決定用
#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

class Enemy : public CharacterBase
{
private:
    //int num;                      // スポーン位置設定用

    int enemy_walk_img[5];          // エネミー歩行画像
    int enemy_death_img[4];         // エネミー死亡画像

    int death_cnt;                  // 死亡アニメーションが終わるまでの時間
    bool is_delete;                 // 削除するか？

    //int image;                    // 現在の表示画像
    int anim_cnt;                   // アニメーション用カウント
    int anim_max_cnt;               // アニメーションカウントの最大値
    int image_num;                  // 表示する画像番号

    bool is_knock_back;             // ノックバックするか？
    bool is_knock_back_start;       // ノックバック開始か？
    bool knock_back_direction;       // ノックバック向き true: 右　false: 左
    //int knock_back_cnt;             // ノックバックの時間

    float player_x;
    float player_y;

public:
    Enemy(float set_x);
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Move();                                // 移動処理
    void ChangeDirection();                     // 進行方向の変更
    void KnockBack();                           // ノックバック処理
    void WalkingAnimation();                    // 歩行アニメーション関係の処理
    void DeathAnimation();                      // 死亡アニメーション関係の処理

    void SetPlayerWorldLocation(World set_world)
    {
        player_x = set_world.x;
        player_y = set_world.y;
    }

    void SetKnockBackFlg(bool set_flg)
    {
        is_knock_back = set_flg;
    }

    void SetKnockBackStartFlg(bool set_flg)
    {
        is_knock_back_start = set_flg;
    }

    void Damege(int damege);                    // 被ダメージ処理

    float GetHp() { return hp; }                // hp取得
    bool GetDeleteFlg() { return is_delete; }   // 削除フラグの取得
};

