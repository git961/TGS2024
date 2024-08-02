#pragma once
#include "ObjectBase.h"

class Geyser : public ObjectBase
{
private:
	int gerser_img;						// 間欠泉画像

	int img_num;						// アニメーション用画像番号
	int anim_cnt;						// アニメーション用カウント
	int water_supply_time;				// 水の供給時間
	bool push_up_flg;					// 水が吹きあがるか？
	int stop_water_time;				// 供給後水を止める時間
	bool stop_water_flg;				// 水が止まっているか？

public:
	Geyser(float set_x, float set_y);
	~Geyser();

	void Update();						// 更新処理
	void Draw() const;					// 描画処理

	void WaterComesOut();				// 水を出す
	bool GetStopWaterFlg() const;		// 水が出ているかの確認
};

