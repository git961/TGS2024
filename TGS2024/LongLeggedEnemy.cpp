#include "LongLeggedEnemy.h"

LongLeggedEnemy::LongLeggedEnemy(float set_x, float set_y)
{
	// 中心座標
	location.x = set_x;
	location.y = set_y;
	world.x = set_x;
	world.y = set_y;
	width = 45.0f;
	height = 64.0f;

	move_x = 1.0f;			// 移動量
	move_y = 0.0f;
	hp = 30.0f;
	speed = 2.0f;
	direction = false;

	// 画像の読み込み
	enemy_img = LoadGraph("images/Enemy/LongLegs.png");
}

LongLeggedEnemy::~LongLeggedEnemy()
{
	// 画像の削除
	DeleteGraph(enemy_img);
}

void LongLeggedEnemy::Update()
{
	// 頂点の設定
	SetVertex();
}

void LongLeggedEnemy::Draw() const
{
	// 脚が長い敵の画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img, TRUE, direction);
}

void LongLeggedEnemy::Move()
{

}

void LongLeggedEnemy::Death()
{

}

void LongLeggedEnemy::DeathAnimation()
{

}
