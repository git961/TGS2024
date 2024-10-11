#pragma once
#include <math.h>
#define _USE_MATH_DEFINES       // M_PI使用用
#include "CharacterBase.h"

class EnemyBase : public CharacterBase
{
protected:
	int death_sound;				// 死亡se

	int anim_cnt;					// アニメーション用カウント
	int enemy_img_num;				// 表示する画像の番号
	int lust_death_img_num;			// 死亡画像の最後の画像番号

	bool play_death_sound_flg;		// 死亡音が鳴ったか？
	bool gem_drop_flg;				// 宝石をドロップするか？
	bool is_delete;					// 自身を削除するか？

	// 星エフェクト
	int star_img;                   // 星エフェクト画像
	bool star_flg;					// 星エフェクトが出るか？
	float star_x;
	float star_y;
	double star_degree;				// 画像の角度（デグリー）
	double star_radian;				// 画像の角度（ラジアン）
	int star_timer;					// 描画時間
	int star_count;					// 三角関数用
	bool star_is_draw;				// 描画するか？
	bool star_direction;            // 向きの一時保管

	float player_world_x;
	float player_world_y;

public:
	EnemyBase();
	~EnemyBase();

protected:

	void Update(GameMainScene* gamemain)override = 0;
	void Draw()const override = 0;
	void HitReaction(ObjectType set_type) override {};

	virtual void Move() = 0;
	virtual void Death() = 0;
	virtual void DeathAnimation() = 0;

	void PlayDeathSound();					// 死亡音を1回だけ再生する処理
	void StarEffectPreparation();			// 星エフェクトの準備
	void StarEffect();                      // 星エフェクトの処理

public:
	void Damage(float damage);

	float GetHp() const;
	float GetAttack() const;
	bool GetGemDropFlg() const;
	bool GetDeleteFlg() const;

	void SetPlayerWorldLocation(World set_world);
	void SetStarFlg();
};