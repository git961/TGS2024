#pragma once
#include "ObjectBase.h"

class Magma : public ObjectBase
{
private:
	int magma_img[10];				// マグマの画像
	int magma_effect_img[4];		// マグマのeffect画像

	int img_num;				// アニメーション用画像番号
	int anim_cnt;				// アニメーション用カウント

	int effect_img_num;				// アニメーション用画像番号
	int effect_anim_cnt;				// アニメーション用カウント

	bool is_any_damage;			// 落ちる床と当たっていたらダメージを与えない

	int magma_se;				// マグマのse
	int volume;					// se音量

public:
	Magma(float set_x, float set_y);
	~Magma();

	void Update();				// 更新処理
	void Draw() const;			// 描画処理

	bool GetAnyDamageFlg()const;

	// is_any_damageフラグをfalseにする
	void NullificationDamage();
	void StopSE();						// マグマのseを止める

private:
	void Animation();			// マグマのアニメーション
	void CheckPlaySound();		// サウンドを再生するか調べる
};