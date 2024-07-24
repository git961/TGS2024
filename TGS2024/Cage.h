#pragma once
#include "ObjectBase.h"

class Cage : public ObjectBase
{
private:
	int cage_img;						// 檻の画像

	int img_num;						// 画像番号
	int anim_cnt;						// アニメーション用カウント
	bool open_flg;						// 入口が開いたか？

public:
	Cage();
	~Cage();

	void Update();						// 更新処理
	void Draw() const;					// 描画処理

public:
	void DoorOpenAnimation();			// ドアが開くアニメーション

private:
	void SetOpenFlg(bool set_flg);

	bool GetOpenFlg() const;

};

