#include "FragileWall.h"

FragileWall::FragileWall(float set_x, float set_y)
{
	world.x = set_x - 32.0f;
	world.y = set_y - 32.0f;
	location.x = world.x;
	location.y = world.y;
	width = 128.0f;
	height = 128.0f;

	wall_state = WallState::GLOW;
	LoadDivGraph("images/Stage/Gimmick/Fragile_Wall.png", 11, 7, 2, 128, 128, fragile_wall_img);
	hp = 40.0f;
	img_num = 0;
	anim_cnt = 0;
	anim_wait_time = 0;
	delete_flg = false;			// 削除しない
}

FragileWall::~FragileWall()
{
	for (int i = 0; i < 11; i++)
	{
		// 画像の削除
		DeleteGraph(fragile_wall_img[i]);
	}
}

// 更新処理
void FragileWall::Update()
{
	// 頂点の設定
	SetVertex();

	switch(wall_state)
	{
	case WallState::GLOW:
		if (anim_wait_time >= 120)
		{
			GlowingAnimation();
		}
		else
		{
			anim_wait_time++;
		}
		CheckBroken();
		break;

	case WallState::BREAK:
		BrokenAnimation();
		break;

	default:
		break;
	}
}

// 描画処理
void FragileWall::Draw() const
{
	// 画像描画
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, fragile_wall_img[img_num], TRUE);

	//DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

// 壊れるアニメーション
void FragileWall::BrokenAnimation()
{
	if (anim_cnt <= 4)
	{
		anim_cnt++;
	}
	else
	{
		anim_cnt = 0;

		// 画像切り替え
		img_num++;

		if (img_num > 11)
		{
			img_num = 10;

			// 削除する
			delete_flg = true;
		}
	}
}

// つやつや光るアニメーション
void FragileWall::GlowingAnimation()
{
	if (anim_cnt <= 4)
	{
		anim_cnt++;
	}
	else
	{
		anim_cnt = 0;

		// 画像切り替え
		img_num++;

		// 画像が一通り切り替え終わったら
		if (img_num > 6)
		{
			img_num = 0;
			// もう一度待つ
			anim_wait_time = 0;
		}
	}
}

// 壊れたか調べる
void FragileWall::CheckBroken()
{
	if (hp <= 0)
	{
		anim_cnt = 0;
		img_num = 7;
		wall_state = WallState::BREAK;
	}
}

// 被ダメージ処理
void FragileWall::Damage(float damage)
{
	hp -= damage;
}
