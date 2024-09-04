#pragma once
#include "ObjectBase.h"
class Key :
    public ObjectBase
{
private:
	int key_img[5];				// 宝石画像
	int effect_img[4];			// ゲットしたときのエフェクト
	int gem_score;				// 宝石のスコア

	bool is_delete;				// 削除してもいいか？

	int anim_cnt;
	int anim_num;
	int effect_num;				// エフェクト画像番号
	int effect_anim_cnt;		// 取得時エフェクトの表示時間
	bool draw_effect;			// エフェクトを表示するか？

	double size;//画像サイズ

public:
	Key(int set_type,float set_x,float set_y);
	~Key();

	void Update();
	void Draw() const;

private:
	void KeyAnim();					// 宝石のアニメーション
};

