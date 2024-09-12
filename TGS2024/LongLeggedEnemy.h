#pragma once
#include "EnemyBase.h"

class LongLeggedEnemy : public EnemyBase
{
private:
	enum class EnemyState
	{
		WALK,
		ATTACK,
		DEATH
	};

	EnemyState enemy_state;

	int enemy_img[5];						// 脚が長い敵の顔の画像
	int enemy_leg_img[5];					// 脚の画像

	int enemy_leg_img_num;					// 脚の画像番号
	float leg_location_y;					// 脚のY座標

	// int footsteps_sound;            // 足音se

	float first_world_y;				// 最初のY座標（高さ）
	float attack_max_y;					// 攻撃時にどこまで下がるのか

	int rising_interval;				// 攻撃で下降後、上昇するまでの間隔

	float player_world_x;
	float player_world_y;

	bool attack_flg;					// true:攻撃中

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

	void WalkAnimation();

public:
	void SetPlayerWorldLocation(World set_world);	// プレイヤーの位置を保持する
};

