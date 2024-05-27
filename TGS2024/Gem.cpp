#include "Gem.h"

Gem::Gem(World set_world, int set_score)
{
	location.x = set_world.x;
	location.y = set_world.y;

	world.x = set_world.x;
	world.y = set_world.y;

	width = 32.0f;
	height = 32.0f;

	// 画像の読み込み
	gem_img = LoadGraph("images/Gem/Gem.png");

	gem_score = set_score;
	count = 0;
	move_x_timer = 0;
	size = 0.0;

	player_x = 0.0f;
	player_y = 0.0f;

	just_generated = true;
}

Gem::~Gem()
{

}

void Gem::Update(GameMainScene* gamemain)
{
	// 宝石が上下に揺れる
	world.y = world.y - sinf(M_PI * 2 / 60 * count) * 0.5;

	if (count < 60)
	{
		count++;
	}
	else
	{
		count = 0;
	}

	if (just_generated == true)
	{
		// 敵の死亡位置がプレイヤーよりも右
		if (world.x > player_x)
		{
			// 宝石が右に移動
			world.x += 15.0f;
		}
		else
		{
			// 宝石が左に移動
			world.x -= 15.0f;

		}
		just_generated = false;
	}

	// 画面外に出ないように
	if (world.x + width / 2 > FIELD_WIDTH)
	{
		world.x -= width / 2;
	}
	else if(world.x - width / 2 < 0)
	{
		world.x += width / 2;
	}

	// だんだんサイズが大きくなる
	if (size < 1.0)
	{
		size += 0.1;
	}
	else
	{
		size = 1.0;
	}


	//if (move_x_timer < 30)
	//{
	//	// 敵の死亡位置がプレイヤーよりも右
	//	if (world.x > player_x)
	//	{
	//		// 宝石が右に移動
	//		world.x += 5.0f;
	//	}
	//	else
	//	{
	//		// 宝石が左に移動
	//		world.x -= 5.0f;

	//	}
	//	move_x_timer++;
	//}
}

void Gem::Draw() const
{
	//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xffffff, true);				// 当たり判定のボックス
	//DrawFormatString(location.x - 100, 50, 0xffffff, "s: %.2lf", size);

	// 宝石画像
	DrawRotaGraph((int)location.x, (int)location.y, size, 0.0, gem_img, TRUE, direction);
}
