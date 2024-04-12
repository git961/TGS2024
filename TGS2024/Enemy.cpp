#include "Enemy.h"

Enemy::Enemy(int set_type)
{
	// 中心座標
	x = 50;
	y = 600;

	width = 30;
	height = 30;

	move_x = 1;			// 移動量
	move_y = 0;			// 未使用
	hp = 10;
	attack = 10;
	speed = 3;			// なくても良い

	type = set_type;

	srand(time(NULL));
	num = rand() % 10 + 1;
	if (num >= 5)
	{
		direction = true;
	}
	else
	{
		direction = false;
	}

	// 進行方法が左ならx座標と移動方向が変わる
	if (direction == false)
	{
		x = 1260;
		move_x *= -1;
	}
}

Enemy::~Enemy()
{

}

void Enemy::Update(GameMainScene* gamemain)
{
	// 移動処理
	x += speed * move_x;

	// 端に来たら跳ね返る、敵同士の当たり判定で使用するかも
	if (x + width / 2 > 1280 || x - width / 2 < 0)
	{
		move_x *= -1;
	}
}

void Enemy::Draw() const
{
#ifdef DEBUG
	DrawFormatString(0, 50, 0xffffff, "hp : %f", hp);

#endif // DEBUG

	// 当たり判定のボックス
	DrawBoxAA(x - width / 2, y - width / 2, x + width / 2, y + height / 2, 0xffffff, true);
	// 中心座標
	DrawCircleAA(x, y, 1, 0xff00ff, true);

}

// 被ダメージ処理
void Enemy::Damege(int damege)
{
	hp -= (float)damege;
}
