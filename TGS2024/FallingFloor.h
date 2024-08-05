#pragma once
#include "ObjectBase.h"

class FallingFloor : public ObjectBase
{
private:
	int falling_floor_img;				// 落ちる床の画像

	float hp;							// 体力
	int img_num;						// アニメーション用画像番号
	int anim_cnt;						// アニメション用カウント
	bool touched_ground;				// 地面に触れたか？

public:
	FallingFloor(float set_x, float set_y);
	~FallingFloor();

	void Update();			// 更新処理
	void Draw() const;		// 描画処理

	void Damage(float damage);			// 被ダメージ処理
	void StopFalling();					// 床の落下を止める
};

