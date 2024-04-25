#pragma once

#define _USE_MATH_DEFINES       // M_PI使用用

//デグリーからラジアンに変換
#define DEGREE_RADIAN(_deg) (M_PI*(_deg)/180.0f)

#include <stdlib.h>         // スポーン位置決定用
#include <time.h>           // スポーン位置決定用
#include "CharacterBase.h"
#include "GameMainScene.h"

class GameMainScene;

// 転がる敵
class RollingEnemy : public CharacterBase
{
private:
	//int num;        // スポーン位置設定用
	//int death_cnt;  // 死亡アニメーションが終わるまでの時間
    int enemy_roll_img[5];  // エネミー画像
    int enemy_effect_img[5];  // エフェクト画像

    int anim_cnt;       // アニメーション用カウント
    bool decrease;      // アニメーション用カウント減少フラグ
    int enemy_image_num;       // エネミー画像表示番号
    int effect_image_num;       // エフェクト画像表示番号

    double angle;        // 画像の角度
    double degree;       // 角度計算用

    bool is_delete;      // 削除するか？

public:

    RollingEnemy();
    ~RollingEnemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Damege(int damege);                // 被ダメージ処理

    float GetHp() { return hp; }            // hp取得
    bool GetDeleteFlg() { return is_delete; } // 削除フラグの取得

};

