#pragma once
#include "ObjectBase.h"

class Magma : public ObjectBase
{
private:
	int magma_img;				// マグマの画像

	int img_num;				// アニメーション用画像番号
	int anim_cnt;				// アニメーション用カウント

public:
	Magma(float set_x, float set_y);
	~Magma();

	void Update();				// 更新処理
	void Draw() const;			// 描画処理
};

