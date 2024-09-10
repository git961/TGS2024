#pragma once
#include "EnemyBase.h"

class HardEnemy : public EnemyBase
{
private:
	int enemy_img[10];						// 敵の画像

	int anim_wait_time;						// 生きているときのアニメーション開始までの待ち時間

public:
	HardEnemy(float set_x, float set_y);
	~HardEnemy();

	void Update() override;
	void Draw() const override;

private:
	void Move() override;
	void Death() override;
	void DeathAnimation() override;

	// 生きているときのアニメーション
	void LivingAnimation();

};

