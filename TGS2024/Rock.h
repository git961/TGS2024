#pragma once
#include "ObjectBase.h"
#include "Define.h"
#include <math.h>

struct block_effect2
{
	float x;
	float y;
	double degree;      // 画像の角度（デグリー）
	double radian;      // 画像の角度（ラジアン）
	int timer;          // 描画時間
	int count;          // 三角関数用
	bool is_draw;       // 描画するか？
};

class Rock :
    public ObjectBase
{
private:
	int rock_img[7];
	int rock_effect_img[3];
	int rock_num;
	int rock_effect_num;

	float hp;

	int fragment_img[4];

	float shakex;
	int shake_cnt;
	bool shake_flg;


	float helx, hely;//helmetのｘｙ
	float frames;
	bool can_jump;
	float radperframe;
	float angle;
	bool is_up;
	int delete_cnt;//消すまでのカウント


	bool effect_flg;
	block_effect2 fragment[4] = { 0 };
	float v0[4];                      // 斜方投射時の初速度
	float gravity;                    // 重力
	float start_x;
	float start_y;
	float sum_t;
	float t;
	float mvx[4];
	float mvy[4];
	bool gem_drop;

	bool delete_flg;

public:
    Rock(int type_num,float set_x, float set_y);
    ~Rock();

	void Update(GameMainScene* gamemain);
	void Draw() const override;

	void FragmentEffect();                      // 石の破片エフェクトの処理
	void FragmentSet();

	void SetDamage(float damage) { hp = hp - damage; }
	void SetShakeFlg(bool set_flg) { shake_flg = set_flg; }
	float GetHp() { return hp; }
	void SetUp(bool set_flg) { is_up = set_flg; }
	bool GetDeleteFlg() { return delete_flg; }
};

