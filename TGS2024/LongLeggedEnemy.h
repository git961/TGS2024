#pragma once
#include "EnemyBase.h"

class LongLeggedEnemy : public EnemyBase
{
private:
	enum class EnemyState
	{
		WALK,
		WAIT,
		ATTACK,
		DEATH
	};

	EnemyState enemy_state;

	int enemy_img[5];						// 脚が長い敵の顔の画像
	int enemy_leg_img[13];					// 脚の画像
	int crack_img[2];						// ヒビ画像

	int enemy_leg_img_num;					// 脚の画像番号
	float leg_location_y;					// 脚のY座標

	// int footsteps_sound;            // 足音se

	float first_world_y;				// 最初のY座標（高さ）
	float attack_max_y;					// 攻撃時にどこまで下がるのか

	int rising_interval;				// 攻撃で下降後、上昇するまでの間隔

	bool attack_flg;					// true:攻撃中
	int attack_anim_count;				// 攻撃アニメーション用カウント

	float hit_enemy_x;

	int attack_wait_time;				// 攻撃の待ち時間
	float now_attack_hight;				// 現在の攻撃の高さ

public:
	LongLeggedEnemy(float set_x, float set_y);
	~LongLeggedEnemy();

	void Update() override;
	void Draw() const override;

private:
	void Move() override;
	void Death() override;
	void DeathAnimation() override;

	void Attack();
	void CheckDistanceToPlayer();			// プレイヤーとの距離を調べる
	void CheckDeathCondition();				// 死亡状態になったか調べる

	void WalkAnimation();					// 歩行アニメーション
	void AttackAnimation();					// 攻撃アニメーション

public:
	void ChangeDirection();
	void SetHitEnemyX(float set_x) { hit_enemy_x = set_x; }
	void SetGemDropFlg(bool set_flg) { gem_drop_flg = set_flg; }
};

