#include "Cage.h"

Cage::Cage(float set_x, float set_y)
{
	// 檻のドアの座標から檻の座標を求める
	world.x = set_x - 192.0f;
	world.y = set_y - 64.0f;
	location.x = world.x;
	location.y = world.y;
	width = 490.0f;
	height = 256.0f;

	cage_img = LoadGraph("images/Stage/Gimmick/Cage.png");
	cage_grate_img = LoadGraph("images/Stage/Gimmick/Cage_Grate.png");

	inside_flg = false;				// プレイヤーは檻の中にいない
}

Cage::~Cage()
{
	// 画像の削除
	DeleteGraph(cage_img);
	DeleteGraph(cage_grate_img);
}

// 更新処理
void Cage::Update()
{
	// 頂点の設定
	SetVertex();
}

// 描画処理
void Cage::Draw() const
{
	// 檻（箱）画像の描画
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, cage_img, TRUE);

	if (inside_flg == false)
	{
		// 格子画像の描画
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, cage_grate_img, TRUE);
	}
	else
	{
		// アルファブレンドの設定
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

		// 格子画像の描画
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, cage_grate_img, TRUE);

		// ノーブレンドにする
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
	// 頂点の確認
	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

void Cage::SetInsideFlg(bool set_flg)
{
	inside_flg = set_flg;
}
