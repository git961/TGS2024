#include "LongLeggedEnemy.h"

LongLeggedEnemy::LongLeggedEnemy(float set_x, float set_y)
{
	// 中心座標
	world.x = set_x;
	world.y = set_y;
	location.x = set_x;
	location.y = set_y;
	width = 45.0f;
	height = 64.0f;

	move_x = -1.0f;			// 移動量
	move_y = 1.0f;
	hp = 30.0f;
	speed = 2.0f;
	direction = false;

	enemy_state = EnemyState::WALK;

	// 画像の読み込み
	enemy_img = LoadGraph("images/Enemy/LongLegs.png");

	first_world_y = world.y;
	attack_max_y = first_world_y + 100.0f;

	rising_interval = 30;

	player_world_x = 0.0f;
	player_world_y = 0.0f;

	attack_flg = false;				// 攻撃中ではない
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

	switch (enemy_state)
	{
		case EnemyState::WALK:
			Move();
			CheckDistanceToPlayer();

			if (attack_flg == true)
			{
				enemy_state = EnemyState::ATTACK;		// 攻撃状態に遷移
			}

			CheckDeathCondition();
			break;

		case EnemyState::ATTACK:
			Attack();

			if (attack_flg == false)
			{
				enemy_state = EnemyState::WALK;			// 歩行状態に遷移
			}

			CheckDeathCondition();
			break;

		case EnemyState::DEATH:
			Death();
			DeathAnimation();
			break;

		default:
			break;
	}
}

void LongLeggedEnemy::Draw() const
{
	// 脚が長い敵の画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img, TRUE, direction);

	DrawFormatString((int)location.x, (int)location.y, 0xffff00, "hp: %.1f", hp);
}

void LongLeggedEnemy::Move()
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

void LongLeggedEnemy::Death()
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

void LongLeggedEnemy::DeathAnimation()
{

}

void LongLeggedEnemy::Attack()
{
	// 下まで来たら
	if (world.y >= attack_max_y)
	{
		if (rising_interval >= 0)
		{
			rising_interval--;
			return;
		}

		move_y = -1.0f;					// 上に上がる
	}

	// 縦移動
	world.y += speed * move_y;

	// 元の高さに戻ったら
	if (world.y <= first_world_y)
	{
		attack_flg = false;					// 攻撃終了
		move_y = 1.0f;
		rising_interval = 30;
	}
}

void LongLeggedEnemy::CheckDistanceToPlayer()
{
	// 敵とプレイヤーのX座標の距離
	float distance = fabsf(world.x - player_world_x);
	if (distance < 100.0f)
	{
		// 攻撃開始
		attack_flg = true;
	}
}

void LongLeggedEnemy::CheckDeathCondition()
{
	if (hp <= 0.0f)
	{
		enemy_state = EnemyState::DEATH;			// 死亡状態に遷移
	}
}

void LongLeggedEnemy::SetPlayerWorldLocation(World set_world)
{
	player_world_x = set_world.x;
	player_world_y = set_world.y;
}
