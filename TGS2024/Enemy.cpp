#include "Enemy.h"

Enemy::Enemy()
{
	width = 30;
	height = 30;
	x = 300;
	y = 300;
}

Enemy::~Enemy()
{
}

void Enemy::Update(GameMainScene* gamemain)
{
}

void Enemy::Draw() const
{
	DrawBoxAA(x-width/2, y-width/2, x+width/2, y+height/2, 0xffffff, true);
	DrawCircleAA(x, y, 1, 0xff00ff, true);
}
