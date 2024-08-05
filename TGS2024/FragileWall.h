#pragma once
#include "ObjectBase.h"

class FragileWall : public ObjectBase
{
private:
	int fragile_wall_img;				// 脆い壁の画像

	float hp;							// 体力
	int img_num;						// 画像番号
	int anim_cnt;						// アニメーション用カウント
	bool broken_flg;					// 壊れたか？
	bool delete_flg;					// 削除するか？

public:
	FragileWall(float set_x, float set_y);
	~FragileWall();

	void Update();						// 更新処理
	void Draw() const;					// 描画処理

private:
	void BrokenAnimation();				// 壊れるアニメーション

public:
	void Damage(float damage);            // 被ダメージ処理

	bool GetDeleteFlg() const { return delete_flg; }

};