#pragma once

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
    int enemy_roll_img[5];          // エネミー画像
    int enemy_effect_img[4];        // エフェクト画像

    int roll_sound;                 // 転がるse
    int death_sount;                // 死亡se
    bool sound_play;                // 1回だけサウンドを鳴らす用

    int anim_cnt;                // アニメーション用カウント
    bool decrease;               // アニメーション用カウント減少フラグ
    int enemy_image_num;         // エネミー画像表示番号
    int effect_image_num;        // エフェクト画像表示番号

    double angle;        // 画像の角度
    double degree;       // 角度計算用

    bool is_delete;      // 削除するか？
    bool just_death;     // 死亡したばかりか？
    bool gem_drop;       // 宝石を落とすか？

public:

    RollingEnemy(float set_x);
    ~RollingEnemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Damege(int damege);                // 被ダメージ処理

    float GetHp() const { return hp; }            // hp取得
    float GetAttack() const { return attack; }// 攻撃力取得
    bool GetDeleteFlg() const { return is_delete; } // 削除フラグの取得
    bool GetGemDropFlg() const { return gem_drop; }
};

