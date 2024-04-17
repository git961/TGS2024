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

public:

    RollingEnemy();
    ~RollingEnemy();

    void Update(GameMainScene* gamemain);
    void Draw() const;

    void Damege(int damege);                // 被ダメージ処理

    float GetHp() { return hp; }            // hp取得
    //int GetDeathCnt() { return death_cnt; } // 死亡アニメーション終了時間の取得

};

