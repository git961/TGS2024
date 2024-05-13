#pragma once
#define DEBUG		        // デバッグ用、消すと#ifdef DEBUGの処理がされなくなる

#include <stdlib.h>         // スポーン位置決定用
#include <time.h>           // スポーン位置決定用
#include <math.h>
#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

class Enemy : public CharacterBase
{
private:
    //int num;                      // スポーン位置設定用

    int enm_death_sound;//死亡SE

    int enemy_walk_img[5];          // エネミー歩行画像
    int enemy_death_img[4];         // エネミー死亡画像
    int knock_back_img;             // ノックバック画像
    int dust_img;                   // エフェクト画像
    int crack_img[2];               // ひび割れ画像
    int star_img;                   // 星エフェクト画像

    int opacity;                    // 画像の不透明度
    int move_x_img;                 // 画像の移動量
    double size;                    // 画像の大きさ
    double degree;                  // 画像の角度

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

    float star_x;                     // 星画像の座標
    float star_y;                     // 星画像の座標
    int count;                        // sin用のカウント
    bool is_draw_star;                // 星を描画するか？

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
    void DrawDust() const;                      // ノックバック時の土埃エフェクト描画
    void KnockBackPreparation();                // ノックバック準備処理
    void StarEffect();                          // 星エフェクト関係の処理
    void Damege(int damege);                    // 被ダメージ処理

    // set関数
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

    void SetDrawStarFlg(bool set_flg)
    {
        is_draw_star = set_flg;
    }

    // get関数
    float GetHp() { return hp; }                        // hp取得
    bool GetDeleteFlg() { return is_delete; }           // 削除フラグの取得
    bool GetIsKnockBack() { return is_knock_back; }     // ノックバックフラグの取得
};

