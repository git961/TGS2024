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
	attack = 30.0f;

	move_x = -1.0f;			// 移動量
	move_y = 1.0f;
	hp = 30.0f;
	speed = 1.0f;
	direction = false;
	hit_enemy_x = 0.0f;

	enemy_state = EnemyState::WALK;

	// 画像の読み込み
	LoadDivGraph("images/Enemy/Rebound.png", 12, 5, 3, 64, 64, enemy_img);
	LoadDivGraph("images/Enemy/Rebound_Crack.png", 2, 2, 1, 64, 64, crack_img);

	angle = 0.0;
	degree = 0.0;

	player_direction = true;

	hit_pickaxe_flg = false;						// つるはしに当たっていない
	roll_left_flg = true;							// 左に転がる
	roll_flg = false;								// 転がっていない
	gem_drop_flg = false;
}

ReboundEnemy::~ReboundEnemy()
{
	// 画像の削除
	for (int i = 0; i < 12; i++)
	{
		DeleteGraph(enemy_img[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(crack_img[i]);
	}
}

void ReboundEnemy::Update(GameMainScene* gamemain)
{
	// 頂点の設定
	SetVertex();

	switch (enemy_state)
	{
	case EnemyState::WALK:
		Move();
		WalkAnimation();
		if (hit_pickaxe_flg == true)
		{
			enemy_state = EnemyState::ROLL;
			enemy_img_num = 7;
		}
		CheckDeathCondition();
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
		// 死亡seの再生
		PlayDeathSound();
		Death();
		DeathAnimation();
		break;

	default:
		break;
	}

	if (star_flg == true)
	{
		StarEffectPreparation();
	}

	// 星を描画するのであれば
	if (star_is_draw == true)
	{
		StarEffect();
	}
}

void ReboundEnemy::Draw() const
{
	switch (enemy_state)
	{
	case EnemyState::WALK:
	case EnemyState::DEATH:
		// つるはしで跳ね返る敵の画像
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, angle, enemy_img[enemy_img_num], TRUE, direction);
		break;

	case EnemyState::ROLL:
		// つるはしで跳ね返る敵の画像
		DrawRotaGraph((int)location.x, (int)location.y + 5, 1.0, angle, enemy_img[enemy_img_num], TRUE, direction);
		// ヒビ画像
		if (hp <= 10.0f)
		{
			DrawRotaGraph((int)location.x, (int)location.y + 5, 1.0, angle, crack_img[1], TRUE, direction);
		}
		else if (hp <= 20.0f)
		{
			DrawRotaGraph((int)location.x, (int)location.y + 5, 1.0, angle, crack_img[0], TRUE, direction);
		}
		break;

	default:
		break;
	}

	if (star_is_draw == true)
	{
		// 星描画
		DrawRotaGraph((int)star_x, (int)star_y, 1.0, star_radian, star_img, TRUE, star_direction);
	}

	//DrawFormatString((int)location.x, (int)location.y, 0xffff00, "hp: %.1f", hp);
}

void ReboundEnemy::HitReaction(ObjectType set_type)
{
}

void ReboundEnemy::Move()
{
	// ステージの端に来たら死亡
	if (world.x + width / 2 > FIELD_WIDTH || world.x - width / 2 < 0)
	{
		hp = 0.0f;
	}

	// 横移動
	world.x += speed * move_x;
}

void ReboundEnemy::Death()
{
	if (anim_cnt <= 90)
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
	// 画像切り替え
	if (anim_cnt != 0)
	{
		// 死亡
		// 5カウントごとに変わる
		enemy_img_num = anim_cnt / 5 + 8;

		if (enemy_img_num > 11)
		{
			enemy_img_num = 11;			// 最終画像で止める
		}
	}
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
	if (player_direction == false)
	{
		// 右に転がる
		roll_left_flg = false;
		move_x = 1.0f;
	}
	else
	{
		move_x = -1.0f;
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
		anim_cnt = 0;

		degree = 0.0;
		// 画像の角度
		angle = DEGREE_RADIAN(degree);
		gem_drop_flg = true;
	}
}

void ReboundEnemy::WalkAnimation()
{
	if (anim_cnt < 68)
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
		// 5カウントごとに変わる
		enemy_img_num = anim_cnt / 10;
	}
}

void ReboundEnemy::SetPlayerDirection(bool set_direction)
{
	player_direction = set_direction;
}

bool ReboundEnemy::GetRollFlg() const
{
	return roll_flg;
}

void ReboundEnemy::SetHitPickaxeFlg()
{
	hit_pickaxe_flg = true;
}

bool ReboundEnemy::GetGemDropFlg() const
{
	return gem_drop_flg;
}

void ReboundEnemy::ChangeDirection()
{
	// 移動量の反転
	move_x *= -1;

	if (direction == false)
	{
		// 左向きに変更
		direction = true;
		if (roll_left_flg == false)
		{
			roll_left_flg = true;
		}
	}
	else
	{
		// 右向きに変更
		direction = false;
		if (roll_left_flg == true)
		{
			roll_left_flg = false;
		}
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