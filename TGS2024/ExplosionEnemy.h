#pragma once
#include "EnemyBase.h"

class ExplosionEnemy : public EnemyBase
{
private:
	enum class EnemyState
	{
		WALK,
		EXPLOSION,						// 爆発
		DEATH
	};

	EnemyState enemy_state;

	int enemy_img;						// 爆発する敵の画像

	// int footsteps_sound;            // 足音se

	int explosion_wait_time;			// 爆発するまでの時間

public:
	ExplosionEnemy(float set_x, float set_y);
	~ExplosionEnemy();

	void Update() override;
	void Draw() const override;

private:
	void Move() override;
	void Death() override;
	void DeathAnimation() override;

	// 爆発処理
	void Explosion();

	// 死亡状態に遷移するか調べる
	void CheckDeathCondition();
};
