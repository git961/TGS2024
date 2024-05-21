#include "Gem.h"

Gem::Gem(World set_world)
{
	location.x = set_world.x;
	location.y = set_world.y;

	world.x = set_world.x;
	world.y = set_world.y;

	width = 32.0f;
	height = 32.0f;

	// 画像の読み込み
	gem_img = LoadGraph("images/Gem/Gem.png");

	gem_score = 10;
}

Gem::~Gem()
{

}

void Gem::Update(GameMainScene* gamemain)
{

}

void Gem::Draw() const
{
	// 宝石画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, gem_img, TRUE, direction);
}
