#include "ReboundEnemy.h"

ReboundEnemy::ReboundEnemy(float set_x, float set_y)
{
	// 中心座標
	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	width = 64.0f;
	height = 64.0f;

	move_x = -1.0f;			// 移動量
	move_y = 1.0f;
	hp = 30.0f;
	speed = 3.0f;
	direction = false;

	enemy_state = EnemyState::WALK;

	// 画像の読み込み
	enemy_img = LoadGraph("images/Enemy/LongLegs.png");

	angle = 0.0;
	degree = 0.0;
}

ReboundEnemy::~ReboundEnemy()
{
	// 画像の削除
	DeleteGraph(enemy_img);
}

void ReboundEnemy::Update()
{
	// 頂点の設定
	SetVertex();

	switch (enemy_state)
	{
	case EnemyState::WALK:
		Move();
		break;

	case EnemyState::ROLL:
		Roll();
		break;

	case EnemyState::DEATH:
		Death();
		DeathAnimation();
		break;

	default:
		break;
	}

}

void ReboundEnemy::Draw() const
{
	// つるはしで跳ね返る敵の画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img, TRUE, direction);

	DrawFormatString((int)location.x, (int)location.y, 0xffff00, "hp: %.1f", hp);

}

void ReboundEnemy::Move()
{

}

void ReboundEnemy::Death()
{

}

void ReboundEnemy::DeathAnimation()
{

}

void ReboundEnemy::Roll()
{

}
