#include "Cage.h"

Cage::Cage()
{
	world.x = 2500.0f;
	world.y = 250.0f;
	location.x = world.x;
	location.y = world.y;
	width = 512.0f;
	height = 256.0f;

	// cage_img = LoadGraph("images/Stage/Cage_Test.png");
	cage_img = LoadGraph("images/Stage/Cage.png");
	img_num = 0;
	anim_cnt = 0;
	open_flg = false;			// ドアが開いてない
}

Cage::~Cage()
{
	// 画像の削除
	DeleteGraph(cage_img);
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
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, cage_img, TRUE);
	
	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

// ドアが開くアニメーション
void Cage::DoorOpenAnimation()
{

}

void Cage::SetOpenFlg(bool set_flg)
{
	open_flg = set_flg;
}

bool Cage::GetOpenFlg() const
{
	return open_flg;
}
