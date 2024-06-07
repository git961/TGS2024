#include "RollingEnemy.h"

RollingEnemy::RollingEnemy(float set_x)
{
	// 中心座標
	//location.x = 200;
	//location.y = 600;

	world.x = set_x;
	world.y = 608.0f;

	width = 60.0f;
	height = 60.0f;

	move_x = -1.0f;			// 移動量
	move_y = 0.0f;			// 未使用
	hp = 10.0f;
	attack = 10.0f;
	speed = 8.0f;
	direction = false;	// 左向き

	//画像読込
	LoadDivGraph("images/Enemy/RollingTest.png", 5, 5, 1, 64, 64, enemy_roll_img);
	LoadDivGraph("images/Enemy/EffectTest.png", 4, 4, 1, 64, 64, enemy_effect_img);

	// サウンド読込
	roll_sound = LoadSoundMem("sounds/se/enemy/roll.mp3");
	death_sount = LoadSoundMem("sounds/se/enemy/death04.mp3");
	sound_play = true;

	anim_cnt = 0;       // アニメーション用カウント
	decrease = false;      // アニメーション用カウント減少フラグ
	enemy_image_num = 0;       // 表示する画像番号
	effect_image_num = 0;

	angle = 0.0;
	degree = 0.0;

	is_delete = false;

	just_death = false;
	gem_drop = false;

	// サウンドの音量設定
	ChangeVolumeSoundMem(255, roll_sound);
	ChangeVolumeSoundMem(100, death_sount);

	stop_move_flg = false;

}

RollingEnemy::~RollingEnemy()
{
	// 画像削除
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(enemy_roll_img[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(enemy_effect_img[i]);
	}

	// サウンド削除
	DeleteSoundMem(roll_sound);
	DeleteSoundMem(death_sount);

}

void RollingEnemy::Update(GameMainScene* gamemain)
{
	if (hp > 0)
	{
		if (CheckSoundMem(roll_sound) == FALSE)
		{
			// 転がるse
			PlaySoundMem(roll_sound, DX_PLAYTYPE_BACK);
		}

		if (stop_move_flg == false)
		{
			if (direction == true)
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

			// 移動処理
			world.x += speed * move_x;
		}
	}
	else
	{
		if (sound_play == true)
		{
			if (CheckSoundMem(death_sount) == FALSE)
			{
				// 死亡se
				PlaySoundMem(death_sount, DX_PLAYTYPE_BACK);
				sound_play = false;
			}
		}

		if (anim_cnt < 74)
		{
			// アニメーション用カウント増加
			anim_cnt++;
		}
		else
		{
			// hpがなくなり、一定時間経ったら削除
			is_delete = true;

			// なくてもいい
			//anim_cnt = 0;
		}

		if (anim_cnt != 0)
		{
			// エネミー画像番号の計算、5カウントごとに画像番号が変わる
			enemy_image_num = anim_cnt / 5;

			if (enemy_image_num > 4)
			{
				enemy_image_num = 4;
			}

			if (enemy_image_num == 4)
			{
				// エフェクト画像番号の計算、15カウントごとに画像番号が変わる
				effect_image_num = (75 - anim_cnt) / 15;
			}
		}

		if (anim_cnt < 2)
		{
			just_death = true;
		}
		else
		{
			if (just_death == true)
			{
				just_death = false;
			}
		}

		if (just_death == true)
		{
			// 宝石を落とす
			gem_drop = true;
		}
		else
		{
			gem_drop = false;
		}

		angle = 0.0;
	}

	/*
	// 端に来たら跳ね返る
	if (world.x + width / 2 > FIELD_WIDTH || world.x - width / 2 < 0)
	{
		//　画像の回転方向を変える
		if (direction == true)
		{
			// 左回転に変更
			direction = false;
		}
		else
		{
			// 右回転に変更
			direction = true;
		}

		// -1を掛けて移動量反転
		move_x *= -1;
	}
	*/
}

void RollingEnemy::Draw() const
{
#ifdef DEBUG
	DrawFormatString(0, 50, 0xffffff, "hp : %f", hp);
	DrawFormatString(0, 200, 0xffffff, "flg%d", stop_move_flg);
	//DrawFormatString(location.x - 100, 530, 0xffffff, "enemy_image_num : %d", enemy_image_num);
	//DrawBoxAA(location.x - width / 2, location.y - width / 2, location.x + width / 2, location.y + height / 2, 0x3c3c3c, true);			// 当たり判定のボックス
#endif // DEBUG


	// エネミー画像の描画（回転させる、右回転、左回転がある）
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, angle, enemy_roll_img[enemy_image_num], TRUE, FALSE);

	if (enemy_image_num == 4)
	{
		// エフェクト画像の描画
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, angle, enemy_effect_img[effect_image_num], TRUE, FALSE);
	}

#ifdef DEBUG
	//DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);				// 中心座標
#endif // DEBUG
}

// 被ダメージ処理
void RollingEnemy::Damege(int damege)
{
	hp -= (float)damege;
}