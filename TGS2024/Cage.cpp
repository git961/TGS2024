#include "Cage.h"

Cage::Cage()
{
	world.x = 2500.0f;
	world.y = 250.0f;
	location.x = world.x;
	location.y = world.y;
	width = 512.0f;
	height = 256.0f;

	cage_img = LoadGraph("images/Stage/Cage.png");
	cage_grate_img = LoadGraph("images/Stage/Cage_Grate.png");
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

	// 格子画像の描画
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, cage_grate_img, TRUE);
	
	// 頂点の確認
	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}
