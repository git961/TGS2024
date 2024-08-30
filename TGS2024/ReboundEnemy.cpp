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
	speed = 2.0f;
	direction = false;

	enemy_state = EnemyState::WALK;

	// 画像の読み込み
	enemy_img = LoadGraph("images/Enemy/Rebound.png");

	angle = 0.0;
	degree = 0.0;

	player_world_x = 0.0f;
	player_world_y = 0.0f;

	hit_pickaxe_flg = false;						// つるはしに当たっていない
	roll_left_flg = true;							// 左に転がる
	roll_flg = false;								// 転がっていない
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
		CheckDeathCondition();
		if (hit_pickaxe_flg == true)
		{
			enemy_state = EnemyState::ROLL;
		}
		break;

	case EnemyState::ROLL:
		if (hit_pickaxe_flg == true)
		{
			CheckDirectionRolling();
		}
		ChangeAngle();
		Move();
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

void ReboundEnemy::Draw() const
{
	// つるはしで跳ね返る敵の画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, angle, enemy_img, TRUE, direction);

	DrawFormatString((int)location.x, (int)location.y, 0xffff00, "hp: %.1f", hp);
}

void ReboundEnemy::Move()
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

void ReboundEnemy::Death()
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

void ReboundEnemy::DeathAnimation()
{

}

void ReboundEnemy::ChangeAngle()
{
	if (roll_left_flg == false)
	{
		// 右回り
		if (degree < 360.0)
		{
			degree += (double)speed;
		}
		else
		{
			degree = 0.0;
		}
	}
	else
	{
		// 左回り
		if (degree > 0.0)
		{
			degree -= (double)speed;
		}
		else
		{
			degree = 360.0;
		}
	}

	// 画像の角度
	angle = DEGREE_RADIAN(degree);
}

void ReboundEnemy::CheckDirectionRolling()
{
	if (world.x >= player_world_x)
	{
		// 右に転がる
		roll_left_flg = false;
		move_x = 1.0f;
	}

	speed = 4.0f;
	roll_flg = true;
	hit_pickaxe_flg = false;
}

void ReboundEnemy::CheckDeathCondition()
{
	if (hp <= 0.0f)
	{
		enemy_state = EnemyState::DEATH;			// 死亡状態に遷移
	}
}

void ReboundEnemy::SetPlayerWorldLocation(World set_world)
{
	player_world_x = set_world.x;
	player_world_y = set_world.y;
}

bool ReboundEnemy::GetRollFlg() const
{
	return roll_flg;
}

void ReboundEnemy::SetHitPickaxeFlg()
{
	hit_pickaxe_flg = true;
}