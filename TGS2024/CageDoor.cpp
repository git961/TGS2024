#include "CageDoor.h"

CageDoor::CageDoor(float set_x, float set_y)
{
	world.x = set_x - 32.0f;
	world.y = set_y - 32.0f;
	location.x = world.x;
	location.y = world.y;
	width = 128.0f;
	height = 128.0f;

	// 画像の読み込み
	LoadDivGraph("images/Stage/Gimmick/Cage_Door.png", 5, 5, 1, 128, 128, cage_door_img);
	img_num = 0;

	hp = 40.0f;
	damage_received = 0;
	img_num = 0;
	anim_cnt = 0;
	receive_damage_flg = false;
	open_flg = false;			// ドアが開いてない
}

CageDoor::~CageDoor()
{
	// 画像の削除
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(cage_door_img[i]);
	}
}

void CageDoor::Update()
{
	// 頂点の設定
	SetVertex();
	if (open_flg == false)
	{
		if (receive_damage_flg == true)
		{
			// ドアが開くアニメーション
			DoorOpenAnimation();
		}
	}
}

void CageDoor::Draw() const
{
	// ドアの画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, cage_door_img[img_num], TRUE);

	DrawFormatString((int)location.x, (int)location.y, 0xff0000, "anim_cnt; %d", anim_cnt);

	// 頂点の確認
	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

// ドアが開くアニメーション
void CageDoor::DoorOpenAnimation()
{
	if (anim_cnt < 3)
	{
		anim_cnt++;
	}
	else
	{
		anim_cnt = 0;

		if (img_num < 4)
		{
			// 画像切り替え
			img_num++;
		}

		if (damage_received > 10.0f)
		{
			damage_received -= 10.0f;
		}
		else
		{
			damage_received = 0.0f;
			receive_damage_flg = false;
		}

		if (img_num >= 4)
		{
			if (hp <= 0.0f)
			{
				// ドアが開いた
				open_flg = true;
			}
		}
	}
}

bool CageDoor::GetOpenFlg() const
{
	return open_flg;
}

// 被ダメージ処理
void CageDoor::Damage(float damage)
{
	damage_received = damage;
	hp -= damage;
	// ダメージを受けた
	receive_damage_flg = true;
}