#pragma once
#include "ObjectBase.h"

class Geyser : public ObjectBase
{
private:
	int geyser_img[6];						// 間欠泉の水画像
	int geyser_hill_img[4];				// 間欠泉の丘画像

	float original_y;//配置された時のｙを入れる

	int hill_img_num;					// 丘の画像番号
	int hill_anim_cnt;					// 丘のアニメーション用カウント
	float hill_y;						// 丘のY座標
	float now_water_height;				// 現在の水の高さ

	int top_geyser_img_num;				// 水の上部画像の番号
	int middle_geyser_img_num;			// 水の中部画像の番号
	int under_geyser_img_num;			// 水の下部画像の番号

	//int img_num;						// アニメーション用画像番号
	int anim_cnt;						// アニメーション用カウント
	int water_supply_time;				// 水の供給時間
	bool push_up_flg;					// 水が吹きあがるか？
	int stop_water_time;				// 供給後水を止める時間
	bool stop_water_flg;				// 水が止まっているか？

	bool draw_middle_flg;				// 2番目の水画像を描画するか？
	bool draw_under_flg;				// 3番目の水画像を描画するか？

public:
	Geyser(float set_x, float set_y);
	~Geyser();

	void Update();						// 更新処理
	void Draw() const;					// 描画処理

private:
	void LaunchWater();					// 水を打ち上げる
	void StopWater();					// 水を止める

	void GeyserAnimation();				// 水のアニメーション
	void HillAnimation();				// 丘のアニメーション

public:
	void WaterComesOut();				// 水を出す
	bool GetStopWaterFlg() const;		// 水が出ているかの確認
};

