#pragma once
#include "EnemyBase.h"

class HardEnemy : public EnemyBase
{
private:
	enum class EnemyState
	{
		LIVE,
		DEATH
	};

	EnemyState enemy_state;

	int enemy_img[10];						// 敵の画像

	int anim_wait_time;						// 生きているときのアニメーション開始までの待ち時間
	int delete_wait_time;					// 削除するまでの待ち時間

public:
	HardEnemy(float set_x, float set_y);
	~HardEnemy();

	void Update() override;
	void Draw() const override;

private:
	void Move() override;
	void Death() override;
	void DeathAnimation() override;

	void LivingAnimation();					// 生きているときのアニメーション
	void CheckDeathCondition();				// 死亡状態になったか調べる

public:
	void SetGemDropFlg(bool set_flg) { gem_drop_flg = set_flg; }
};

