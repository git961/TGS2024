#pragma once
#include "ObjectBase.h"
#include "GameMainScene.h"
#include "Player.h"
#include <math.h>
class GameMainScene;
class Player;

class Dynamite :
    public ObjectBase
{
private:
    float move_x;
    float rotation;
    int dynamite_img;
    int explosion_img[10];
    int dynamite_flg;//爆発したらTRUE
    bool damage_flg;
    bool dynamite_death;//ダイナマイト消去フラグ
    int direction;

    int explosion_num;
    int explosion_cnt;

    int attack;           // 攻撃力
    float enemy_x;          // 当たった敵の座標
    float tmp_abs;

    int bomb_sound;//爆発音
public:
    Dynamite(World set_xy,int set_direction);
    ~Dynamite();
    void Update();
    void Draw() const;
    void DamageCalculation();       // ダメージの計算

    void SetDynamite(bool set_flg) { dynamite_flg = set_flg; }
    void SetEnemyX(float set_x) { enemy_x = set_x; }

    bool GetDynamite() { return dynamite_flg; }
    bool Getdamage_flg() { return damage_flg; }
    bool Getdeath_flg() { return dynamite_death; }
    int GetAttack() { return attack; }
    float GetTmpAbs()const { return tmp_abs; }
};

