#pragma once
#include "EnemyBase.h"

class LongLeggedEnemy : public EnemyBase
{
private:
	int enemy_img;						// 脚が長い敵の画像

	// int footsteps_sound;            // 足音se

public:
	LongLeggedEnemy(float set_x, float set_y);
	~LongLeggedEnemy();

	void Update() override;
	void Draw() const override;

private:
	void Move() override;
	void Death() override;
	void DeathAnimation() override;

};

