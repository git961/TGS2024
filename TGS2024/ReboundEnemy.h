#pragma once
#include "EnemyBase.h"

class ReboundEnemy : public EnemyBase
{
private:
	enum class EnemyState
	{
		WALK,
		ROLL,
		DEATH
	};

	EnemyState enemy_state;
	int enemy_img;						// つるはしで跳ね返る敵の画像

	double angle;						// 画像の角度
	double degree;						// 角度計算用

public:
	ReboundEnemy(float set_x, float set_y);
	~ReboundEnemy();
	void Update() override;
	void Draw() const override;

private:
	void Move() override;
	void Death() override;
	void DeathAnimation() override;

	void Roll();
};

