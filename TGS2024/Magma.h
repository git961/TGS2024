#pragma once
#include "ObjectBase.h"

class Magma : public ObjectBase
{
private:
	int magma_img[5];				// マグマの画像

	int img_num;				// アニメーション用画像番号
	int anim_cnt;				// アニメーション用カウント

	bool is_any_damage;			// 落ちる床と当たっていたらダメージを与えない

public:
	Magma(float set_x, float set_y);
	~Magma();

	void Update();				// 更新処理
	void Draw() const;			// 描画処理

	bool GetAnyDamageFlg()const;

	// is_any_damageフラグをfalseにする
	void NullificationDamage();

private:
	void Animation();			// マグマのアニメーション
};

