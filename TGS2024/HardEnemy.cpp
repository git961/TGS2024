#include "HardEnemy.h"

HardEnemy::HardEnemy(float set_x, float set_y)
{
	// 中心座標
	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	width = 128.0f;
	height = 128.0f;

	hp = 30.0f;
	direction = false;

	enemy_img = LoadGraph("images/Enemy/Hard.png");
}

HardEnemy::~HardEnemy()
{
	// 画像の削除
	DeleteGraph(enemy_img);
}

void HardEnemy::Update()
{
	if (hp <= 0.0f)
	{
		// 死亡処理
		Death();
		DeathAnimation();
	}
}

void HardEnemy::Draw() const
{
	// ダイナマイトでしか倒せない敵の画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img, TRUE, direction);

	DrawFormatString((int)location.x, (int)location.y, 0xffff00, "hp: %.1f", hp);
}

void HardEnemy::Move()
{

}

void HardEnemy::Death()
{
	if (anim_cnt <= 30)
	{
		anim_cnt++;
	}
	else
	{
		// 削除
		is_delete = true;
	}
}

void HardEnemy::DeathAnimation()
{

}