#pragma once
#define DEBUG		        // デバッグ用、消すと#ifdef DEBUGの処理がされなくなる

//#include <stdlib.h>         // スポーン位置決定用
//#include <time.h>           // スポーン位置決定用
#include <math.h>
#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

struct effect
{
    float x;
    float y;
    double degree;      // 画像の角度（デグリー）
    double radian;      // 画像の角度（ラジアン）
    int timer;          // 描画時間
    int count;          // 三角関数用
    bool is_draw;       // 描画するか？
};

class Enemy : public CharacterBase
{
private:
    int enemy_walk_img[5];          // エネミー歩行画像
    int enemy_death_img[4];         // エネミー死亡画像
    int knock_back_img;             // ノックバック画像
    int crack_img[2];               // ひび割れ画像
    int star_img;                   // 星エフェクト画像
    int fragment_img[4];            // 石の破片エフェクト画像
    
    int death_cnt;                  // 死亡アニメーションが終わるまでの時間
    bool is_delete;                 // 削除するか？

    int anim_cnt;                   // アニメーション用カウント
    int anim_max_cnt;               // アニメーションカウントの最大値
    int image_num;                  // 表示する画像番号
    int crack_image_num;            // ひび割れ画像番号

    bool is_knock_back;             // ノックバックするか？
    bool is_knock_back_start;       // ノックバック開始か？

    float player_x;
    float player_y;

    effect star;
    bool tmp_direction;               // 向きの一時保管

    effect fragment[4];

public:
    Enemy(float set_x);
    ~Enemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Move();                                // 移動処理
    void ChangeDirection();                     // 進行方向の変更
    void KnockBack();                           // ノックバック処理
    void WalkingAnimation();                    // 歩行アニメーションの処理
    void DeathAnimation();                      // 死亡アニメーションの処理
    void KnockBackPreparation();                // ノックバック準備処理
    void StarEffect();                          // 星エフェクトの処理
    void FragmentEffect();                      // 石の破片エフェクトの処理
    void Damege(int damege);                    // 被ダメージ処理

    // set関数
    void SetPlayerWorldLocation(World set_world)
    {
        player_x = set_world.x;
        player_y = set_world.y;
    }

    void SetKnockBackStartFlg(bool set_flg)
    {
        is_knock_back_start = set_flg;
    }

    // get関数
    float GetHp() const { return hp; }                        // hp取得
    float GetAttack() const{ return attack; }                 // 攻撃力取得
    bool GetDeleteFlg() const { return is_delete; }           // 削除フラグの取得
    bool GetIsKnockBack() const { return is_knock_back; }     // ノックバックフラグの取得
};

