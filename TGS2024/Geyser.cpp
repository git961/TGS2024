#include "Geyser.h"

Geyser::Geyser(float set_x, float set_y)
{
	world.x = set_x;
	world.y = set_y;
	location.x = world.x;
	location.y = world.y;
	width = 64.0f;
	height = 64.0f;

	// 画像の読み込み
	//geyser_img = LoadGraph("images/Stage/Gimmick/Geyser.png");
	LoadDivGraph("images/Stage/Gimmick/Geyser.png", 6, 2, 3, 64, 64, geyser_img);
	LoadDivGraph("images/Stage/Gimmick/Geyser_Hill.png", 4, 4, 1, 128, 64, geyser_hill_img);

	hill_img_num = 0;
	hill_anim_cnt = 0;
	hill_y = location.y;
	now_water_height = 0.0f;

	top_geyser_img_num = 0;
	middle_geyser_img_num = 2;
	under_geyser_img_num = 4;

	//img_num = 0;
	anim_cnt = 0;
	water_supply_time = 360;		// 6秒間水が出る
	push_up_flg = false;			// 水は打ちあがらない
	stop_water_time = 180;			// 供給後3秒かけて水が止まる
	stop_water_flg = true;			// 水は止まっている

	draw_middle_flg = false;
	draw_under_flg = false;
}

Geyser::~Geyser()
{
	// 画像の削除
	for (int i = 0; i < 6; i++)
	{
		DeleteGraph(geyser_img[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(geyser_hill_img[i]);
	}
}

// 更新処理
void Geyser::Update()
{
	// 頂点の更新
	SetVertex();

	// 丘の描画座標の更新
	hill_y = location.y;

	// 水が出ているなら
	if (stop_water_flg == false)
	{
		if (push_up_flg == true)
		{
			// 水を打ち上げる
			LaunchWater();
		}
		else
		{
			// 水を止めていく
			StopWater();
		}

		// 丘のY座標の計算
		hill_y += now_water_height;

		// 水のアニメーション
		GeyserAnimation();
		// 丘のアニメーション
		HillAnimation();
	}
}

// 描画処理
void Geyser::Draw() const
{
	//if (stop_water_flg == false)
	//{
	//	// 間欠泉画像の描画
	//	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, geyser_img[top_geyser_img_num], TRUE);
	//	if (draw_middle_flg)
	//	{
	//		DrawRotaGraph((int)location.x, (int)location.y + 64, 1.0, 0.0, geyser_img[middle_geyser_img_num], TRUE);
	//	}
	//	if (draw_under_flg)
	//	{
	//		DrawRotaGraph((int)location.x, (int)location.y + 128, 1.0, 0.0, geyser_img[under_geyser_img_num], TRUE);
	//	}
	//}

	// 丘画像の描画
	DrawRotaGraph((int)location.x, (int)hill_y, 1.0, 0.0, geyser_hill_img[hill_img_num], TRUE);

	// 頂点の確認
	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

// 水を打ち上げる
void Geyser::LaunchWater()
{
	if (water_supply_time > 180)
	{
		// 上に移動
		world.y--;

		// 水の高さ
		now_water_height++;
	}
	else if (water_supply_time <= 0)
	{
		// 水の打ち上げを止める
		push_up_flg = false;

		// 水の供給時間の再設定（6秒間）
		water_supply_time = 360;
	}

	water_supply_time--;

	// 水の画像を表示する
	if (now_water_height >= 64)
	{
		draw_middle_flg = true;
	}
	if (now_water_height >= 128)
	{
		draw_under_flg = true;
	}
}

// 水を止める
void Geyser::StopWater()
{
	if (stop_water_time > 0)
	{
		// 元の高さに戻る
		world.y++;
		now_water_height--;
		stop_water_time--;

		// 水の画像を非表示にする
		if (now_water_height <= 128)
		{
			draw_under_flg = false;
		}
		if (now_water_height <= 64)
		{
			draw_middle_flg = false;
		}
	}
	else
	{
		// 水が止まった
		stop_water_flg = true;

		// 供給後から水が止まるまでの時間の再設定（3秒）
		stop_water_time = 180;

		now_water_height = 0.0f;
		hill_img_num = 0;
	}
}

// 水のアニメーション
void Geyser::GeyserAnimation()
{
	if (anim_cnt < 10)
	{
		anim_cnt++;
	}
	else
	{
		anim_cnt = 0;
		top_geyser_img_num++;
		middle_geyser_img_num++;
		under_geyser_img_num++;

		if (top_geyser_img_num > 1)
		{
			top_geyser_img_num = 0;
			middle_geyser_img_num = 2;
			under_geyser_img_num = 4;
		}
	}
}

// 丘のアニメーション
void Geyser::HillAnimation()
{
	if (hill_anim_cnt < 10)
	{
		hill_anim_cnt++;
	}
	else
	{
		hill_anim_cnt = 0;
		hill_img_num++;

		if (hill_img_num > 3)
		{
			hill_img_num = 1;
		}
	}
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