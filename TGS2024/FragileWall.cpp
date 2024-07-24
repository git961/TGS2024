#include "FragileWall.h"

FragileWall::FragileWall()
{
	world.x = 2500.0f;
	world.y = 500.0f;
	location.x = world.x;
	location.y = world.y;
	width = 128.0f;
	height = 128.0f;

	fragile_wall_img = LoadGraph("images/Stage/Fragile_Wall.png");
	hp = 100.0f;
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
}

// 描画処理
void FragileWall::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, fragile_wall_img, TRUE);

	DrawBox((int)box_vertex.right_x, (int)box_vertex.upper_y, (int)box_vertex.left_x, (int)box_vertex.lower_y, 0x00ffff, FALSE);
}
