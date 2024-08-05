#include "Geyser.h"

Geyser::Geyser(float set_x, float set_y)
{
	world.x = set_x;
	world.y = set_y;
	location.x = world.x;
	location.y = world.y;
	width = 64.0f;
	height = 64.0f;

	gerser_img = LoadGraph("images/Stage/Gimmick/Geyser.png");

	img_num = 0;
	anim_cnt = 0;
	water_supply_time = 360;		// 6秒間水が出る
	push_up_flg = false;			// 水は打ちあがらない
	stop_water_time = 180;			// 供給後3秒かけて水が止まる
	stop_water_flg = true;			// 水は止まっている
}

Geyser::~Geyser()
{
	// 画像の削除
	DeleteGraph(gerser_img);
}

// 更新処理
void Geyser::Update()
{
	// 頂点の更新
	SetVertex();

	// 水が出ているなら
	if (stop_water_flg == false)
	{
		// 水を打ち上げるなら
		if (push_up_flg == true)
		{
			if (water_supply_time > 180)
			{
				// 上に移動
				world.y--;
			}
			water_supply_time--;

			if (water_supply_time <= 0)
			{
				// 水の打ち上げを止める
				push_up_flg = false;

				// 水の供給時間の再設定（6秒間）
				water_supply_time = 360;
			}
		}
		else
		{
			// 水を止めていく

			if (stop_water_time > 0)
			{
				// 元の高さに戻る
				world.y++;
				stop_water_time--;
			}
			else
			{
				// 水が止まった
				stop_water_flg = true;

				// 供給後から水が止まるまでの時間の再設定（3秒）
				stop_water_time = 180;
			}
		}
	}
}

// 描画処理
void Geyser::Draw() const
{
	// 間欠泉画像の描画
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, gerser_img, TRUE);

	// 頂点の確認
	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

// 水を噴き出す
void Geyser::WaterComesOut()
{
	// 水が打ちあがる
	push_up_flg = true;

	// 水が出ている
	stop_water_flg = false;
}

bool Geyser::GetStopWaterFlg() const
{
	return stop_water_flg;
}
