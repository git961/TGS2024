#include "Jem.h"

Jem::Jem(World set_world)
{
	location.x = set_world.x;
	location.y = set_world.y;

	world.x = set_world.x;
	world.y = set_world.y;

	width = 32.0f;
	height = 32.0f;

	// 画像の読み込み
	jem_img = LoadGraph("images/Jem/Jem.png");
}

Jem::~Jem()
{

}

void Jem::Update(GameMainScene* gamemain)
{

}

void Jem::Draw() const
{
	// 宝石画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, jem_img, TRUE, direction);
}
