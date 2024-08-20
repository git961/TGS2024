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

	int enemy_img;						// 脚が長い敵の画像

	// int footsteps_sound;            // 足音se

	float first_world_y;				// 最初のY座標（高さ）
	float attack_max_y;					// 攻撃時にどこまで下がるのか

	int rising_interval;				// 攻撃で下降後、上昇するまでの間隔

	float player_world_x;
	float player_world_y;

	bool attack_flg;					// true:攻撃中
	bool original_height_flg;			// 元の高さに戻るか？

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
	void CheckDistanceToPlayer();
	void CheckDeathCondition();

public:
	void SetPlayerWorldLocation(World set_world);
};

