﻿#include "Enemy.h"

Enemy::Enemy(float set_x)
{
	// 中心座標
	//location.x = 400 + (40 * set_x);
	//location.y = 600;

	world.x = 400.0f + (120.0f * set_x);
	world.y = 600.0f;

	width = 45.0f;
	height = 64.0f;

	move_x = 1.0f;			// 移動量
	move_y = 0.0f;			// 未使用
	hp = 30.0f;
	attack = 10.0f;
	speed = 2.0f;

	//画像読込
	//LoadDivGraph("images/Enemy/EnemyTest01.png", 9, 3, 1, 64, 64, chara_image);
	LoadDivGraph("images/Enemy/WalkTest.png", 5, 5, 1, 64, 64, enemy_walk_img);
	LoadDivGraph("images/Enemy/WalkDeathTest.png", 4, 4, 1, 64, 64, enemy_death_img);

	anim_cnt = 0;
	anim_max_cnt = 19;

	// 現在の画像
	//image = 0;
	image_num = 0;

	death_cnt = 0;
	is_delete = false;

	direction = false;			// 画像は右向き

	is_knock_back = false;		// ノックバックしない
	is_knock_back_start = false;
	knock_back_direction = true;
	//knock_back_cnt = 90;		// ノックバック時間

	player_x = 0.0f;
	player_y = 0.0f;

	//srand(time(NULL));
	//num = rand() % 10 + 1;
	//if (num >= 5)
	//{
	//	direction = true;
	//}
	//else
	//{
	//	direction = false;
	//}

	//// 進行方法が左ならx座標と移動方向が変わる
	//if (direction == false)
	//{
	//	x = 1260;
	//	move_x *= -1;
	//}
}

Enemy::~Enemy()
{
	// 画像の削除
	//for (int i = 0; i < 10; i++) {
	//	DeleteGraph(chara_image[i]);
	//}
}

void Enemy::Update(GameMainScene* gamemain)
{
	if (is_knock_back == true && hp > 0)
	{
		if (is_knock_back_start == true)
		{
			// ノックバック時の初期スピード
			speed = 5.0f;

			if (world.x > player_x)
			{
				// 右にノックバックする
				knock_back_direction = true;
			}
			else
			{
				// 左にノックバックする
				knock_back_direction = false;
			}
		}

		// ノックバック処理
		KnockBack();
	}
	else
	{
		if (hp > 0)
		{
			// 移動処理
			Move();

			// 歩行アニメーション
			WalkingAnimation();
		}
		else
		{
			// 死亡アニメーション
			DeathAnimation();
		}
	}
}

void Enemy::Draw() const
{
#ifdef DEBUG
	DrawFormatString(location.x - 100, 50, 0xffffff, "speed : %.1f", speed);
	DrawFormatString(location.x - 100, 80, 0xffffff, "is_k: %d", is_knock_back);
	//DrawFormatString(location.x - 100, 50, 0xffffff, "d : %d", direction);
	//DrawFormatString(location.x - 100, 70, 0xffffff, "l.x : %.1f", location.x);
	//DrawFormatString(location.x - 100, 90, 0xffffff, "l.y : %.1f", location.y);
	//DrawBoxAA(location.x - width / 2, location.y - width / 2, location.x + width / 2, location.y + height / 2, 0xffffff, true);				// 当たり判定のボックス
#endif // DEBUG


	// 画像の描画
	if (hp > 0)
	{
		// 歩行画像
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_walk_img[image_num], TRUE, direction);
	}
	else
	{
		// 死亡画像
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_death_img[image_num], TRUE, direction);
	}


#ifdef DEBUG
	//DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);			// 中心座標
#endif // DEBUG

}

// 移動処理
void Enemy::Move()
{
	// 端に来たら跳ね返る
	if (world.x + width / 2 > FIELD_WIDTH || world.x - width / 2 < 0)
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
	}

	if (speed < 2.0f)
	{
		// 加速処理
		speed += 2.0f / 120;
	}

	// 移動処理
	world.x -= speed * move_x;
}

// 進行方向の変更
void Enemy::ChangeDirection()
{
	// 移動量の反転
	move_x *= -1;

	if (direction == false)
	{
		// 左向きに変更
		direction = true;
		world.x += 4;
	}
	else
	{
		// 右向きに変更
		direction = false;
		world.x -= 4;
	}
}

// ノックバック処理
void Enemy::KnockBack()
{
	//if (knock_back_cnt > 0)
	//{
	//	world.x += 3;
	//	knock_back_cnt--;
	//}
	//else
	//{
	//	is_knock_back = false;
	//	knock_back_cnt = 90;
	//}

	if (speed >= 0.0f)
	{
		if (knock_back_direction == true)
		{
			// 右に移動
			world.x += speed;
		}
		else
		{
			// 左に移動
			world.x -= speed;
		}

		// 減速処理
		speed -= 5.0f / 30;

		// 画面外に出ないようにする
		if (world.x + width / 2 > FIELD_WIDTH)
		{
			world.x = FIELD_WIDTH - width / 2;
		}
		else if (world.x - width / 2 < 0)
		{
			world.x =width / 2+10;

		}
	}
	else
	{
		// ノックバック終了
		is_knock_back = false;
	}

	if (is_knock_back_start == true)
	{
		is_knock_back_start = false;
	}
}

// 歩行アニメーション関係の処理
void Enemy::WalkingAnimation()
{
	if (anim_cnt < anim_max_cnt)
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
		image_num = anim_cnt / 5;
	}
}

// 死亡アニメーション関係の処理
void Enemy::DeathAnimation()
{
	death_cnt++;

	if (death_cnt >= 60)
	{
		// 60カウント以上なら削除フラグをtrueに変更
		is_delete = true;
	}

	// 画像切り替え
	if (death_cnt != 0)
	{
		// 死亡
		// 5カウントごとに変わる
		image_num = death_cnt / 5;

		if (image_num > 3)
		{
			// 最終画像で止める
			image_num = 3;
		}
	}
}

// 被ダメージ処理
void Enemy::Damege(int damege)
{
	hp -= (float)damege;
}