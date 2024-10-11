#include "Enemy.h"

Enemy::Enemy(float set_x, float set_y,bool set_direction)
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
	attack = 10.0f;
	speed = 2.0f;

	enemy_state = EnemyState::WALK;

	//画像読込
	LoadDivGraph("images/Enemy/Walk.png", 11, 5, 3, 64, 64, enemy_img);
	LoadDivGraph("images/Enemy/crack.png", 2, 2, 1, 64, 64, crack_img);
	star_img = LoadGraph("images/Enemy/star.png");
	LoadDivGraph("images/Enemy/fragment.png", 4, 4, 1, 64, 64, fragment_img);

	// サウンド読込
	footsteps_sound = LoadSoundMem("sounds/se/enemy/walk.mp3");
	knock_back_sount = LoadSoundMem("sounds/se/enemy/knockback.mp3");
	death_sount = LoadSoundMem("sounds/se/enemy/death.mp3");
	play_sound = true;

	anim_cnt = 0;
	anim_max_cnt = 19;

	// 現在の画像
	image_num = 0;
	crack_image_num = -1;

	death_cnt = 0;
	is_delete = false;

	direction = set_direction;
	//direction = false;			// 画像は右向き

	is_knock_back = false;		// ノックバック中ではない
	is_knock_back_start = false;

	player_x = 0.0f;
	player_y = 0.0f;

	// 進行方法が左ならx座標と移動方向が変わる
	if (direction == true)
	{
		move_x *= -1;
		world.y = -60;
	}

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

	hit_enemy_x = 0.0f;
	SetVertex();

	// サウンドの音量設定
	ChangeVolumeSoundMem(80, footsteps_sound);
	ChangeVolumeSoundMem(150, knock_back_sount);
	ChangeVolumeSoundMem(255, death_sount);

	if (direction == true)
	{
		fall_end_flg = false;
		enemy_state = EnemyState::FALL;
	}
	else {

		fall_end_flg = true;
	}
	fall_flg = false;

	fragment_draw_flg = true;

	my_object_type = ObjectType::enemy;

}

Enemy::~Enemy()
{
	// 画像の削除
	for (int i = 0; i < 11; i++)
	{
		DeleteGraph(enemy_img[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(crack_img[i]);
	}
	DeleteGraph(star_img);
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(fragment_img[i]);
	}

	// サウンド削除
	DeleteSoundMem(footsteps_sound);
	DeleteSoundMem(knock_back_sount);
	DeleteSoundMem(death_sount);
}

void Enemy::Update(GameMainScene* gamemain)
{
	SetVertex();

	switch (enemy_state)
	{
	case EnemyState::WALK:
		// 移動処理
		Move();
		// 歩行アニメーション
		WalkingAnimation();
		// 足音を鳴らす
		if (CheckSoundMem(footsteps_sound) == FALSE)
		{
			PlaySoundMem(footsteps_sound, DX_PLAYTYPE_BACK);
		}

		if (is_knock_back_start == true)
		{
			enemy_state = EnemyState::KNOCKBACK;
		}
		if (play_sound == false)
		{
			play_sound = true;
		}
		// 死亡状態になったか調べる
		CheckDeathCondition();
		break;

	case EnemyState::KNOCKBACK:
		// 足音を止める
		if (CheckSoundMem(footsteps_sound) == TRUE)
		{
			StopSoundMem(footsteps_sound);
		}
		// ノックバック処理
		KnockBack();
		// 死亡状態になったか調べる
		CheckDeathCondition();
		break;

	case EnemyState::FALL:
		// 落下
		Fall();
		// 落下アニメーション

		if (play_sound == false)
		{
			play_sound = true;
		}

		break;

	case EnemyState::DEATH:
		if (play_sound == true)
		{
			if (CheckSoundMem(death_sount) == FALSE)
			{
				// 死亡se
				PlaySoundMem(death_sount, DX_PLAYTYPE_BACK);
				play_sound = false;
			}
		}

		// 死亡アニメーション
		DeathAnimation();

		if (fragment_draw_flg == true)
		{
			// 破片エフェクト
			FragmentEffect();
		}
		break;

	default:
		break;
	}

	// 星を描画するのであれば
	if (star.is_draw == true)
	{
		StarEffect();
	}
}

void Enemy::Draw() const
{
#ifdef DEBUG
	//DrawFormatString(location.x - 100, 50, 0xffffff, "hp: %.2f", hp);
	//DrawFormatString(location.x - 100, 30, 0xffffff, "crack: %d", crack_image_num);
	//DrawFormatString(location.x - 100, 140, 0xffffff, "3: %.1f", fragment[3].x);
	//DrawFormatString(location.x - 100, 170, 0xffffff, "L: %.1f", location.x);
	//DrawFormatString(location.x - 100, 80, 0xffffff, "k: %d", is_knock_back);
	//DrawFormatString(location.x - 100, 50, 0xffffff, "s: %d", is_knock_back_start);
	//DrawFormatString(location.x - 100, 50, 0xffffff, "worldy;%f", world.y);
	//DrawFormatString(location.x - 100, 80, 0xffffff, "pworldy;%f", player_x);
	//DrawFormatString(100, 20, 0xffffff, "opacity: %d", opacity);
	//DrawBoxAA(location.x - width / 2, location.y - height / 2, location.x + width / 2, location.y + height / 2, 0xffffff, true);				// 当たり判定のボックス
#endif // DEBUG

	switch (enemy_state)
	{
	case EnemyState::WALK:
		// 歩行画像
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img[image_num], TRUE, direction);
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
		break;

	case EnemyState::KNOCKBACK:
		// ノックバック画像
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img[5], TRUE, direction);
		break;

	case EnemyState::FALL:
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img[10], TRUE, direction);
		break;

	case EnemyState::DEATH:
		// 死亡画像
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img[image_num], TRUE, direction);

		if (fragment_draw_flg == true)
		{
			for (int i = 0; i < 4; i++)
			{
				// 破片描画
				DrawRotaGraph((int)fragment[i].x, (int)fragment[i].y, 1.0, 0.0, fragment_img[i], TRUE, direction);
			}
		}
		break;

	default:
		break;
	}

	if (star.is_draw == true)
	{
		// 星描画
		DrawRotaGraph((int)star.x, (int)star.y, 1.0, star.radian, star_img, TRUE, tmp_direction);
	}

#ifdef DEBUG
	//DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);			// 中心座標
#endif // DEBUG
}

void Enemy::HitReaction(ObjectType set_type)
{
	if (set_type == ObjectType::rock)
	{
		ChangeDirection();
	}

}

// 移動処理
void Enemy::Move()
{
	// ステージの端に来たら跳ね返る
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

	//移動処理
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

// ノックバック処理
void Enemy::KnockBack()
{
	if (play_sound == true)
	{
		if (CheckSoundMem(knock_back_sount) == FALSE)
		{
			// ノックバックse
			PlaySoundMem(knock_back_sount, DX_PLAYTYPE_BACK);
			play_sound = false;
		}
	}

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
		enemy_state = EnemyState::WALK;
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
			image_num = death_cnt / 5 + 6;

			if (image_num > 9)
			{
				// 最終画像で止める
				image_num = 9;
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
	star.y = location.y - abs(sinf((float)M_PI * 2.0f / 60.0f * (float)star.count) * 60.0f);
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
				v0[i] = rand() % 200 + (float)300;

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

		if (fragment[i].y  < world.y + 32.0f)
		{
			// 地面についていない間は値の計算を行う
			mvx[i] = v0[i] * cosf((float)fragment[i].radian) * sum_t;
			mvy[i] = -v0[i] * sinf((float)fragment[i].radian) * sum_t + (gravity * sum_t * sum_t) / 2;

			fragment[i].y = start_y + mvy[i];
		}
		else
		{
			fragment_draw_flg = false;
		}

		fragment[i].x = start_x + mvx[i];

		sum_t += t;

		if (fragment[i].is_draw == false)
		{
			fragment[i].is_draw = true;
		}
	}
}

// 被ダメージ処理
void Enemy::Damage(int damage)
{
	hp -= (float)damage;
}

void Enemy::Fall()
{
	
	if (player_x > world.x+80)
	{
		fall_flg = true;
	}

	if (fall_flg == true)
	{
		world.y += 4;
		if (world.y > 600)
		{
			world.y = 608.0f;
			fall_end_flg = true;
			enemy_state = EnemyState::WALK;
		}
	}

}

// 死亡状態になったか調べる
void Enemy::CheckDeathCondition()
{
	if (hp <= 0.0f)
	{
		anim_cnt = 0;								// 死亡アニメーション用にカウントを0にする
		image_num = 6;								// 死亡画像の最初の画像番号を設定
		enemy_state = EnemyState::DEATH;			// 死亡状態に遷移
	}
}

void Enemy::SetKnockBackStartFlg(bool set_flg)
{
	 is_knock_back_start = set_flg; 
	 is_knock_back = true;

	 // ノックバックの準備
	 KnockBackPreparation();
}
