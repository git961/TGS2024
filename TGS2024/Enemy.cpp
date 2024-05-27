#include "Enemy.h"

Enemy::Enemy(float set_x, float set_y)
{
	// 中心座標
	location.x = set_x;
	location.y = set_y;

	world.x = set_x;
	world.y = set_y + 8.0f;

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
	LoadDivGraph("images/Enemy/crack.png", 2, 2, 1, 64, 64, crack_img);
	star_img = LoadGraph("images/Enemy/star.png");
	LoadDivGraph("images/Enemy/fragment.png", 4, 4, 1, 64, 64, fragment_img);

	anim_cnt = 0;
	anim_max_cnt = 19;

	// 現在の画像
	image_num = 0;
	crack_image_num = -1;

	death_cnt = 0;
	is_delete = false;

	direction = false;			// 画像は右向き

	is_knock_back = false;		// ノックバック中ではない
	is_knock_back_start = false;

	player_x = 0.0f;
	player_y = 0.0f;

	//srand((unsigned int)time(NULL));			// 現在時刻の情報で初期化
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

	star.x = 0.0f;
	star.y = 0.0f;
	star.degree = 0.0;						// 画像の角度
	star.radian = 0.0;						// 画像の角度
	star.timer = 0;
	star.count = 0;
	star.is_draw = false;				// 星の描画なし
	tmp_direction = direction;

	for (int i = 0; i < 4; i++)
	{
		fragment[i].x = 0.0f;
		fragment[i].y = 0.0f;
		fragment[i].timer = 0;
		fragment[i].count = 0;
		fragment[i].is_draw = false;

		// 初速度の設定
		//v0[i] = rand() % 5 + 1;
		v0[i] = 0.0f;

		// 発射角度の設定
		//fragment[i].degree = rand() % 90;
		fragment[i].degree = 0.0;

		if (i < 2)
		{
			fragment[i].degree += 270;
		}

		fragment[i].radian = (double)DEGREE_RADIAN(fragment[i].degree);

		mvx[i] = 0.0f;
		mvy[i] = 0.0f;
	}

	gravity = 980.0f;
	start_x = 0.0f;
	start_y = 0.0f;
	sum_t = 0.0167f;
	t = 0.0167f;

	gem_drop = false;
	draw_death_img = true;
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
	if (hp > 0)
	{
		if (is_knock_back_start == true)
		{
			is_knock_back = true;
		}

		if (is_knock_back == true)
		{
			if (is_knock_back_start == true)
			{
				// ノックバックの準備
				KnockBackPreparation();
			}

			// ノックバック処理
			KnockBack();
		}
		else
		{
			// 移動処理
			Move();

			// 歩行アニメーション
			WalkingAnimation();
		}

		// 星を描画するのであれば
		if (star.is_draw == true)
		{
			StarEffect();
		}
	}
	else
	{
		// 死亡アニメーション
		DeathAnimation();

		// 破片エフェクト
		FragmentEffect();
	}
}

void Enemy::Draw() const
{
#ifdef DEBUG
	//DrawFormatString(location.x - 100, 50, 0xffffff, "f: %d", death_cnt);
	//DrawFormatString(location.x - 100, 50, 0xffffff, "0: %.1f", fragment[0].x);
	//DrawFormatString(location.x - 100, 80, 0xffffff, "1: %.1f", fragment[1].x);
	//DrawFormatString(location.x - 100, 110, 0xffffff, "2: %.1f", fragment[2].x);
	//DrawFormatString(location.x - 100, 140, 0xffffff, "3: %.1f", fragment[3].x);
	//DrawFormatString(location.x - 100, 170, 0xffffff, "L: %.1f", location.x);
	//DrawFormatString(location.x - 100, 230, 0xffffff, "m0: %.1f", mvx[0]);
	//DrawFormatString(location.x - 100, 260, 0xffffff, "m1: %.1f", mvx[1]);
	//DrawFormatString(location.x - 100, 290, 0xffffff, "m2: %.1f", mvx[2]);
	//DrawFormatString(location.x - 100, 170, 0xffffff, "+: %f", start_x + mvx);
	//DrawFormatString(location.x - 100, 80, 0xffffff, "k: %d", is_knock_back);
	//DrawFormatString(location.x - 100, 50, 0xffffff, "s: %d", is_knock_back_start);
	//DrawFormatString(100, 20, 0xffffff, "opacity: %d", opacity);
	//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xffffff, true);				// 当たり判定のボックス
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
		}

		if (star.is_draw == true)
		{
			// 星描画
			DrawRotaGraph((int)star.x, (int)star.y, 1.0, star.radian, star_img, TRUE, tmp_direction);
		}
	}
	else
	{
		if (draw_death_img == true)
		{
			// 死亡画像
			DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_death_img[image_num], TRUE, direction);
		}

		for (int i = 0; i < 4; i++)
		{
			// 破片描画
			DrawRotaGraph((int)fragment[i].x, (int)fragment[i].y, 1.0, 0.0, fragment_img[i], TRUE, direction);
		}
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
			world.x += 4;
		}
		else
		{
			// 右向きに変更
			direction = false;
			world.x -= 4;
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

		if (star.is_draw == true)
		{
			if (crack_image_num < 1)
			{
				crack_image_num++;
			}
		}
	}
}

// 歩行アニメーションの処理
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

// 死亡アニメーションの処理
void Enemy::DeathAnimation()
{
	death_cnt++;

	if (death_cnt >= 120)
	{
		// 120カウント以上なら削除フラグをtrueに変更
		is_delete = true;
	}

	if (draw_death_img == true)
	{
		if (death_cnt >= 60)
		{
			// 死亡画像を非表示に
			draw_death_img = false;
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
}

// ノックバック準備処理
void Enemy::KnockBackPreparation()
{
	// ノックバック時の初期スピード
	speed = 2.0f;

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

	// 星画像用変数
	star.degree = 0.0;
	star.x = location.x;
	star.y = location.y - 40;
	star.count = 0;
	tmp_direction = direction;
}

// 星エフェクトの処理
void Enemy::StarEffect()
{
	// 星の座標を敵のスクリーン座標にする
	star.x = location.x;
	star.y = location.y - abs(sinf(M_PI * 2 / 60 * star.count) * 60);
	star.timer++;

	if (tmp_direction == false)
	{
		// 反時計回り
		if (star.degree > 0.0)
		{
			star.degree -= 4;
		}
		else
		{
			star.degree = 360.0;
		}
	}
	else
	{
		// 時計回り
		if (star.degree < 360.0)
		{
			star.degree += 4;
		}
		else
		{
			star.degree = 0.0;
		}
	}

	// 角度をデグリーからラジアンへ変更
	star.radian = DEGREE_RADIAN(star.degree);

	// 星の画像sin用カウント
	if (star.count < 30)
	{
		star.count++;
	}
	else
	{
		star.count = 0;
	}

	// 星が飛ぶ向き
	if (tmp_direction == false)
	{
		// 左に飛ぶ
		star.x -= (float)star.timer;
	}
	else
	{
		// 右に飛ぶ
		star.x += (float)star.timer;
	}

	if (star.timer > 30)
	{
		star.is_draw = false;
		star.timer = 0;
		star.count = 0;
		star.degree = 0.0;
		star.radian = 0.0;
	}
}

// 石の破片エフェクトの処理
void Enemy::FragmentEffect()
{
	for (int i = 0; i < 4; i++)
	{
		if (fragment[i].is_draw == false)
		{
			srand((unsigned int)time(NULL));			// 現在時刻の情報で初期化
			for (int i = 0; i < 4; i++)
			{
				// 初速度の設定
				//v0[i] = 300.0f;
				v0[i] = rand() % 200 + 300;

				// 発射角度の設定
				fragment[i].degree = rand() % 45 + 45;

				if (i < 2)
				{
					fragment[i].degree += 45;
				}

				fragment[i].radian = (double)DEGREE_RADIAN(fragment[i].degree);
			}

			fragment[i].x = location.x;
			fragment[i].y = location.y - height /  2;				// 画像の中心

			// 宝石を落とす
			gem_drop = true;
		}

		start_x = location.x;
		start_y = location.y - height / 2;				// 画像の中心

		if (fragment[i].y  < 608.f)
		{
			// 地面についていない間は値の計算を行う
			mvx[i] = v0[i] * cosf((float)fragment[i].radian) * sum_t;
			mvy[i] = -v0[i] * sinf((float)fragment[i].radian) * sum_t + (gravity * sum_t * sum_t) / 2;

			fragment[i].y = start_y + mvy[i];
		}
		else
		{
			fragment[i].y = 608.0f;
		}

		fragment[i].x = start_x + mvx[i];

		sum_t += t;

		//if (fragment[i].y <= 608.0f)
		//{
		//	// 地面についていないのであれば
		//	if (fragment[i].timer++ < 60)
		//	{
		//		if (i > 1)
		//		{
		//			// 斜方投射
		//			// 右向き
		//			fragment[i].x += v0[i] * cosf((float)fragment[i].radian);
		//		}
		//		else
		//		{
		//			// 斜方投射
		//			// 左向き
		//			fragment[i].x -= v0[i] * cosf((float)fragment[i].radian);
		//		}

		//		fragment[i].y += v0[i] * sinf((float)fragment[i].radian) - gravity;
		//	}
		//}

		if (fragment[i].is_draw == false)
		{
			fragment[i].is_draw = true;
		}
	}
}

// 被ダメージ処理
void Enemy::Damege(int damege)
{
	hp -= (float)damege;
}