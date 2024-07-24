#include "FragileWall.h"

FragileWall::FragileWall()
{
	world.x = 2500.0f;
	world.y = 550.0f;
	location.x = world.x;
	location.y = world.y;
	width = 128.0f;
	height = 128.0f;

	fragile_wall_img = LoadGraph("images/Stage/Fragile_Wall.png");
	hp = 100.0f;
	img_num = 0;
	anim_cnt = 0;
	broken_flg = false;			// 壊れていない
	delete_flg = false;			// 削除しない
}

FragileWall::~FragileWall()
{
	// 画像の削除
	DeleteGraph(fragile_wall_img);
}

// 更新処理
void FragileWall::Update()
{
	SetVertex();

	if (hp <= 0)
	{
		broken_flg = true;
	}

	if (broken_flg == true)
	{
		// 壊れるアニメーション
		BrokenAnimation();
	}
}

// 描画処理
void FragileWall::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, fragile_wall_img, TRUE);

	DrawFormatString((int)location.x - 50, (int)location.y, 0xffff00, "anim : %d", anim_cnt);

	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}

// 壊れるアニメーション
void FragileWall::BrokenAnimation()
{
	if (anim_cnt < 60)
	{
		anim_cnt++;
	}
	else
	{
		// 削除する
		delete_flg = true;
	}
}

// 被ダメージ処理
void FragileWall::Damege(int damege)
{
	hp -= (float)damege;
}
