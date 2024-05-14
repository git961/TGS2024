#include "RollingEnemy.h"

RollingEnemy::RollingEnemy()
{
	// 中心座標
	//location.x = 200;
	//location.y = 600;

	world.x = 30;
	world.y = 600;

	width = 60;
	height = 60;

	move_x = 1;			// 移動量
	move_y = 0;			// 未使用
	hp = 10;
	attack = 10;
	speed = 1;			// なくても良い
	direction = true;	// 左向き

	//画像読込
	LoadDivGraph("images/Enemy/RollingTest.png", 5, 5, 1, 64, 64, enemy_roll_img);
	LoadDivGraph("images/Enemy/EffectTest.png", 4, 4, 1, 64, 64, enemy_effect_img);

	anim_cnt = 0;       // アニメーション用カウント
	decrease = false;      // アニメーション用カウント減少フラグ
	enemy_image_num = 0;       // 表示する画像番号
	effect_image_num = 0;

	angle = 0.0;
	degree = 0.0;

	is_delete = false;

	//death_cnt = 90;

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

RollingEnemy::~RollingEnemy()
{

}

void RollingEnemy::Update(GameMainScene* gamemain)
{
	if (hp > 0)
	{
		if (direction == true)
		{
			// 右回り
			if (degree < 360.0f)
			{
				degree += speed;
			}
			else
			{
				degree = 0.0f;
			}
		}
		else
		{
			// 左回り
			if (degree > 0.0f)
			{
				degree -= speed;
			}
			else
			{
				degree = 360.0f;
			}
		}

		// 画像の角度
		angle = DEGREE_RADIAN(degree);

		// 移動処理
		world.x += speed * move_x;
	}
	else
	{
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
		angle = 0.0;
	}

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

}

void RollingEnemy::Draw() const
{
#ifdef DEBUG
	//DrawFormatString(0, 50, 0xffffff, "hp : %f", hp);
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