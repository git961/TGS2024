#pragma once
#include "EnemyBase.h"
#include <math.h>

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

	float player_world_x;
	float player_world_y;

	bool hit_pickaxe_flg;				// つるはしに当たったか？
	bool roll_left_flg;					// 左に転がるか？
	bool roll_flg;						// 転がっているか？

public:
	ReboundEnemy(float set_x, float set_y);
	~ReboundEnemy();
	void Update() override;
	void Draw() const override;

private:
	void Move() override;
	void Death() override;
	void DeathAnimation() override;

	// 転がるときの画像角度変更
	void ChangeAngle();

	// 転がる向きを調べる
	void CheckDirectionRolling();

	// 死亡状態に遷移するか調べる
	void CheckDeathCondition();

public:
	void SetPlayerWorldLocation(World set_world);

	bool GetRollFlg() const;

	// つるはしで攻撃された
	void SetHitPickaxeFlg();
};