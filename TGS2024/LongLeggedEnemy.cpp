#include "LongLeggedEnemy.h"

LongLeggedEnemy::LongLeggedEnemy(float set_x, float set_y)
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

	hit_enemy_x = 0.0f;

	enemy_state = EnemyState::WALK;

	// 画像の読み込み
	LoadDivGraph("images/Enemy/LongLegs.png", 5, 5, 1, 64, 64, enemy_img);
	LoadDivGraph("images/Enemy/Leg.png", 8, 5, 2, 128, 128, enemy_leg_img);

	enemy_leg_img_num = 0;
	leg_location_y = location.y;

	first_world_y = world.y;
	attack_max_y = first_world_y + 64.0f;

	rising_interval = 30;

	player_world_x = 0.0f;
	player_world_y = 0.0f;

	attack_flg = false;				// 攻撃中ではない
}

LongLeggedEnemy::~LongLeggedEnemy()
{
	// 画像の削除
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(enemy_img[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(enemy_leg_img[i]);
	}
}

void LongLeggedEnemy::Update()
{
	// 頂点の設定
	SetVertex();

	switch (enemy_state)
	{
	case EnemyState::WALK:
		Move();
		WalkAnimation();
		CheckDistanceToPlayer();
		if (attack_flg == true)
		{
			enemy_state = EnemyState::ATTACK;		// 攻撃状態に遷移
		}

		// 死亡状態になったか調べる
		CheckDeathCondition();
		break;

	case EnemyState::ATTACK:
		Attack();
		if (attack_flg == false)
		{
			enemy_state = EnemyState::WALK;			// 歩行状態に遷移
		}

		// 死亡状態になったか調べる
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
	switch (enemy_state)
	{
	case EnemyState::WALK:
		// 脚の画像
		DrawRotaGraph((int)location.x, (int)leg_location_y, 1.0, 0.0, enemy_leg_img[enemy_leg_img_num], TRUE, direction);
		break;

	default:
		break;
	}

	// 敵の顔の画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img[enemy_img_num], TRUE, direction);

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

	// 脚の画像のY座標更新
	leg_location_y = location.y + 32.0f;
}

void LongLeggedEnemy::Death()
{
	if (anim_cnt <= 40)
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
	// 画像切り替え
	if (anim_cnt != 0)
	{
		// 死亡
		// 5カウントごとに変わる
		enemy_img_num = anim_cnt / 5;

		if (enemy_img_num > 4)
		{
			enemy_img_num = 4;			// 最終画像で止める
		}
	}
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

		// 上に上がる
		move_y = -1.0f;
	}

	// 縦移動
	world.y += speed * move_y;

	// 元の高さに戻ったら
	if (world.y <= first_world_y)
	{
		// 攻撃終了
		attack_flg = false;
		move_y = 1.0f;
		rising_interval = 30;
	}
}

// プレイヤーとの距離を調べる
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

// 死亡状態になったか調べる
void LongLeggedEnemy::CheckDeathCondition()
{
	if (hp <= 0.0f)
	{
		anim_cnt = 0;								// 死亡アニメーション用にカウントを0にする
		enemy_state = EnemyState::DEATH;			// 死亡状態に遷移
		world.y = attack_max_y;
	}
}

void LongLeggedEnemy::WalkAnimation()
{
	if (anim_cnt < 103)
	{
		// アニメーション用カウント増加
		anim_cnt++;
	}
	else
	{
		anim_cnt = 0;
	}

	// 画像切り替え
	if (anim_cnt != 0)
	{
		// 歩行
		enemy_leg_img_num = anim_cnt / 15;
	}
}

// 進行方向の変更
void LongLeggedEnemy::ChangeDirection()
{
	// 移動量の反転
	move_x *= -1;

	if (direction == false)
	{
		// 左向きに変更
		direction = true;
	}
	else
	{
		// 右向きに変更
		direction = false;
	}

	if (world.x > hit_enemy_x)
	{
		world.x += 5;
	}
	else
	{
		world.x -= 5;
	}

}

// プレイヤーの位置を保持する
void LongLeggedEnemy::SetPlayerWorldLocation(World set_world)
{
	player_world_x = set_world.x;
	player_world_y = set_world.y;
}
