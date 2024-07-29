#pragma once
#include "ObjectBase.h"

class CageDoor : public ObjectBase
{
private:
	int cage_door_img;					// 檻のドアの画像

	int img_num;						// 画像番号
	int anim_cnt;						// アニメーション用カウント
	bool open_flg;						// 入口が開いたか？

public:
	CageDoor(float set_x, float set_y);
	~CageDoor();

	void Update();						// 更新処理
	void Draw() const;					// 描画処理

private:
	void DoorOpenAnimation();			// ドアが開くアニメーション

public:
	void SetOpenFlg(bool set_flg);

	bool GetOpenFlg() const;

};