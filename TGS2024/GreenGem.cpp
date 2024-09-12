#include "GreenGem.h"

GreenGem::GreenGem(World set_world, int set_score)
{
	world.x = set_world.x;
	world.y = set_world.y;
	location.x = set_world.x;
	location.y = set_world.y;

	gem_img[0] = LoadGraph("images/Stage/GreenGem.png");
	size = 1.0f;
	width = 50.0f;
	height = 50.0f;

}

GreenGem::~GreenGem()
{
}

void GreenGem::Update(GameMainScene* gamemain)
{
}

void GreenGem::Draw() const
{
	// 宝石画像
	DrawRotaGraph((int)location.x, (int)location.y, size, 0.0, gem_img[0], TRUE, 0);
}
