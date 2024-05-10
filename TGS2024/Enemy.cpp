#include "Enemy.h"

Enemy::Enemy(float set_x)
{
	// 中心座標
	location.x = 400 + (40 * set_x);
	location.y = 600;

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
	LoadDivGraph("images/Enemy/WalkTest.png", 5, 5, 1, 64, 64, enemy_walk_img);
	LoadDivGraph("images/Enemy/WalkDeathTest.png", 4, 4, 1, 64, 64, enemy_death_img);
	knock_back_img = LoadGraph("images/Enemy/KnockBack.png");
	dust_img = LoadGraph("images/Enemy/Dust.png");
	star_img = LoadGraph("images/Enemy/star.png");
	LoadDivGraph("images/Enemy/crack.png", 2, 2, 1, 64, 64, crack_img);


	opacity = 180;				// 画像の不透明度
	move_x_img = 100;
	size = 0.3;					// 画像の大きさ
	degree = 0.0;				// 画像の角度

	anim_cnt = 0;
	anim_max_cnt = 19;

	// 現在の画像
	//image = 0;
	image_num = 0;
	crack_image_num = -1;

	death_cnt = 0;
	is_delete = false;

	direction = false;			// 画像は右向き

	is_knock_back = false;		// ノックバック中ではない
	is_knock_back_start = false;

	player_x = 0.0f;
	player_y = 0.0f;

	srand((unsigned int)time(NULL));			// 現在時刻の情報で初期化
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

	star_x = world.x;
	star_y = world.y - 40;
	count = 0;
	is_draw_star = false;				// 星の描画なし
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
			KnockBackPreparation();
		}

		// 土埃エフェクト用
		move_x_img++;
		opacity -= 4;

		// 星を描画するのであれば
		if (is_draw_star == true)
		{
			StarEffect();
		}

		// ノックバック処理
		KnockBack();
	}
	else
	{
		// 星用
		if (is_draw_star == true)
		{
			is_draw_star = false;
		}

		// 土埃エフェクト用
		if (move_x_img != 1)
		{
			move_x_img = 1;
			opacity = 180;
		}

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
	DrawFormatString(location.x - 100, 50, 0xffffff, "x : %.1f", star_x);
	//DrawFormatString(location.x - 100, 80, 0xffffff, "y : %.1f", star_y);
	//DrawFormatString(location.x - 100, 80, 0xffffff, "k: %d", is_knock_back);
	//DrawFormatString(location.x - 100, 50, 0xffffff, "s: %d", is_knock_back_start);
	//DrawFormatString(100, 20, 0xffffff, "opacity: %d", opacity);
	//DrawBoxAA(location.x - width / 2, location.y - width / 2, location.x + width / 2, location.y + height / 2, 0xffffff, true);				// 当たり判定のボックス
#endif // DEBUG

	// 画像の描画
	if (hp > 0)
	{
		if (is_knock_back == false)
		{
			// 歩行画像
			DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_walk_img[image_num], TRUE, direction);

			if (hp != 30)
			{
				// ひび割れ画像
				if (image_num == 1)
				{
					DrawRotaGraph((int)location.x, (int)location.y + 2, 1.0, 0.0, crack_img[crack_image_num], TRUE, direction);
				}
				else
				{
					DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, crack_img[crack_image_num], TRUE, direction);
				}
			}
		}
		else
		{
			// ノックバック画像
			DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, knock_back_img, TRUE, direction);

			if (is_draw_star == true)
			{
				// 星描画
				DrawRotaGraph((int)star_x, (int)star_y - abs(sinf(M_PI * 2 / 60 * count) * 60), 1.0, degree, star_img, TRUE, direction);
			}

			// 土埃エフェクト
			DrawDust();
		}
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
		speed += 2.0f / 60;
		//speed = 2.0f;
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
	if (speed >= 0.0f)
	{
		if (direction == false)
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
			world.x = width / 2;
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
		if (is_draw_star == true)
		{
			if (crack_image_num < 1)
			{
				crack_image_num++;
			}
		}
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

// ノックバック時のエフェクト描画
void Enemy::DrawDust() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);

	for (int i = 0; i < 3; i++)
	{
		if (direction == false)
		{
			DrawRotaGraph((int)location.x - move_x_img + i * 20, (int)location.y + 20, size + i * 0.15, 0.0, dust_img, TRUE, FALSE);
		}
		else
		{
			// 画像
			DrawRotaGraph((int)location.x + move_x_img - i * 20, (int)location.y + 20, size + i * 0.15, 0.0, dust_img, TRUE, FALSE);
		}
	}

	// ブレンドモードをデフォルトにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// ノックバック準備処理
void Enemy::KnockBackPreparation()
{
	// ノックバック時の初期スピード
	speed = 1.0f;

	// アニメーションカウントを0に戻す
	anim_cnt = 0;

	if (world.x > player_x)
	{
		// 右にノックバックする
		direction = false;
		move_x = 1;
	}
	else
	{
		// 左にノックバックする
		direction = true;
		move_x = -1;
	}
}

// 星エフェクト関係の処理
void Enemy::StarEffect()
{
	if (is_knock_back_start == true)
	{
		// 星画像用変数
		degree = 0.0;
		star_x = location.x;
		star_y = location.y - 40;
		count = 0;
	}

	// 星の画像回転
	if (degree < 360.0)
	{
		degree++;
	}
	else
	{
		degree = 0.0;
	}

	// 星の画像sin用カウント
	if (count < 30)
	{
		count++;
	}
	else
	{
		count = 0;
	}

	// 星が飛ぶ向き
	if (direction == false)
	{
		// 左に飛ぶ
		star_x--;
	}
	else
	{
		// 右に飛ぶ
		star_x++;
	}
}

// 被ダメージ処理
void Enemy::Damege(int damege)
{
	hp -= (float)damege;
}