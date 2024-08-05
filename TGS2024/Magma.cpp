#include "Magma.h"

Magma::Magma(float set_x, float set_y)
{
	world.x = set_x;
	world.y = set_y;
	location.x = world.x;
	location.y = world.y;
	width = 128.0f;
	height = 64.0f;

	magma_img = LoadGraph("images/Stage/Gimmick/Magma.png");

	img_num = 0;
	anim_cnt = 0;
}

Magma::~Magma()
{
	// 画像の削除
	DeleteGraph(magma_img);
}

// 更新処理
void Magma::Update()
{
	// 頂点の更新
	SetVertex();
}

// 描画処理
void Magma::Draw() const
{
	// マグマ画像の描画
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, magma_img, TRUE);

	// 頂点の確認
	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}
