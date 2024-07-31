#include "CageDoor.h"

CageDoor::CageDoor(float set_x, float set_y)
{
	world.x = set_x;
	world.y = set_y;
	location.x = world.x;
	location.y = world.y;
	width = 128.0f;
	height = 128.0f;

	// 画像の読み込み
	cage_door_img = LoadGraph("images/Stage/Cage_Door.png");

	hp = 40.0f;
	img_num = 0;
	anim_cnt = 0;
	open_flg = false;			// ドアが開いてない
}

CageDoor::~CageDoor()
{
	// 画像の削除
	DeleteGraph(cage_door_img);
}

void CageDoor::Update()
{
	// 頂点の設定
	SetVertex();

	if (hp <= 0.0f)
	{
		// ドアが開くアニメーション
		DoorOpenAnimation();
	}
}

void CageDoor::Draw() const
{
	// ドアの画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, cage_door_img, TRUE);

	DrawFormatString((int)location.x, (int)location.y, 0xff0000, "anim_cnt; %d", anim_cnt);

	// 頂点の確認
	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

// ドアが開くアニメーション
void CageDoor::DoorOpenAnimation()
{
	if (anim_cnt < 30)
	{
		anim_cnt++;
	}
	else
	{
		// ドアが開いた
		open_flg = true;
	}

}

bool CageDoor::GetOpenFlg() const
{
	return open_flg;
}

// 被ダメージ処理
void CageDoor::Damege(float damege)
{
	hp -= damege;
}
