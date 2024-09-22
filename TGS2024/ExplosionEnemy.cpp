#include "ExplosionEnemy.h"

ExplosionEnemy::ExplosionEnemy(float set_x, float set_y)
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
	speed = 2.0f;
	direction = false;

	enemy_state = EnemyState::WALK;

	// 画像の読み込み
	enemy_img = LoadGraph("images/Enemy/LongLegs.png");

	explosion_wait_time = 0;
}

ExplosionEnemy::~ExplosionEnemy()
{
	// 画像の削除
	DeleteGraph(enemy_img);
}

void ExplosionEnemy::Update()
{
	// 頂点の設定
	SetVertex();

	switch (enemy_state)
	{
	case EnemyState::WALK:
		Move();

		CheckDeathCondition();
		break;

	case EnemyState::EXPLOSION:
		Explosion();

		break;

	case EnemyState::DEATH:
		Death();
		DeathAnimation();
		break;

	default:
		break;
	}
}

void ExplosionEnemy::Draw() const
{
	// 爆発する敵の画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img, TRUE, direction);

	//DrawFormatString((int)location.x, (int)location.y, 0xffff00, "hp: %.1f", hp);
}

void ExplosionEnemy::Move()
{
	// ステージの端に来たら跳ね返る
	if (world.x + width / 2 > FIELD_WIDTH || world.x - width / 2 < 0)
	{
		// 移動量の反転
		move_x *= -1;
	}

	// 横移動
	world.x += speed * move_x;
}

void ExplosionEnemy::Death()
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

void ExplosionEnemy::DeathAnimation()
{

}

void ExplosionEnemy::Explosion()
{

}

void ExplosionEnemy::CheckDeathCondition()
{
	if (hp <= 0.0f)
	{
		enemy_state = EnemyState::DEATH;			// 死亡状態に遷移
	}
}
