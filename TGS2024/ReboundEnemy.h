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
	int enemy_img[12];						// つるはしで跳ね返る敵の画像
	int crack_img[2];						// ヒビ画像

	double angle;						// 画像の角度
	double degree;						// 角度計算用

	bool player_direction;				// プレイヤーの向き

	bool hit_pickaxe_flg;				// つるはしに当たったか？
	bool roll_left_flg;					// 左に転がるか？
	bool roll_flg;						// 転がっているか？
	float hit_obj_x;					// 当たったオブジェクトのx座標（ワールド）

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

	// 死亡状態に遷移するか調べる
	void CheckDeathCondition();

	// 歩行アニメーション
	void WalkAnimation();

public:
	void SetPlayerDirection(bool set_direction);

	bool GetRollFlg() const;

	// つるはしで攻撃された
	void SetHitPickaxeFlg();
	// 転がる向きを調べる
	void CheckDirectionRolling();
	// 回転向きの変更
	void ChangeDirection();

	void SetHitObjX(float set_x) { hit_obj_x = set_x; }
	bool GetGemDropFlg() const;
	void SetGemDropFlg(bool set_flg) { gem_drop_flg = set_flg; }
};