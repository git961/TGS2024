#include "FragileWall.h"

FragileWall::FragileWall()
{
	world.x = 2500.0f;
	world.y = 550.0f;

	width = 64.0f;
	height = 64.0f;

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

}

// 描画処理
void FragileWall::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, fragile_wall_img, TRUE);
}
