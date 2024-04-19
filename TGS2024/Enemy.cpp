#include "Enemy.h"

Enemy::Enemy(float set_x)
{
	// 中心座標
	//location.x = 400 + (40 * set_x);
	//location.y = 600;

	world.x = 400 + (80 * set_x);
	world.y = 600;

	width = 45;
	height = 64;

	move_x = 1;			// 移動量
	move_y = 0;			// 未使用
	hp = 10;
	attack = 10;
	speed = 3;			// なくても良い


	//画像読込
	//LoadDivGraph("images/Enemy/EnemyTest01.png", 9, 3, 1, 64, 64, chara_image);
	LoadDivGraph("images/Enemy/WalkTest.png", 5, 5, 1, 64, 64, enemy_walk_img);
	LoadDivGraph("images/Enemy/WalkDeathTest.png", 4, 4, 1, 64, 64, enemy_death_img);

	anim_cnt = 0;
	// 現在の画像
	//image = 0;
	decrease = false;
	image_num = 0;

	death_cnt = 0;
	is_delete = false;

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
	if (hp > 0)
	{
		if (decrease == false)
		{
			if (anim_cnt < 99)
			{
				// アニメーション用カウント増加
				anim_cnt++;
			}
			else
			{
				anim_cnt = 0;
				//decrease = true;
			}
		}
		//else
		//{
		//	if (anim_cnt > 0)
		//	{
		//		// アニメーション用カウント減少
		//		anim_cnt--;
		//	}
		//	else
		//	{
		//		decrease = false;
		//	}
		//}
	}
	else
	{
		death_cnt++;

		if (death_cnt >= 60)
		{
			is_delete = true;
		}
	}

	// 画像切り替え
	if (hp > 0)
	{
		if (anim_cnt != 0)
		{	
			// 20カウントごとに変わる
			image_num = anim_cnt / 20;
		}
	}
	else
	{
		if (death_cnt != 0)
		{
			image_num = death_cnt / 5;
		}

		if (image_num > 3)
		{
			image_num = 3;
		}
	}

	//if (hp > 0)
	//{
	//	// 移動処理
	//	//x += speed * move_x;

	//	//// 端に来たら跳ね返る、敵同士の当たり判定で使用するかも
	//	//if (x + width / 2 > 1280 || x - width / 2 < 0)
	//	//{
	//	//	move_x *= -1;
	//	//}
	//}

}

void Enemy::Draw() const
{
#ifdef DEBUG
	DrawFormatString(0, 50, 0xffffff, "death_cnt : %d", death_cnt);
	DrawFormatString(200, 50, 0xffffff, "image_num : %d", image_num);
	//DrawFormatString(400, 50, 0xffffff, "image : %d", image);

#endif // DEBUG

	// 当たり判定のボックス
	//DrawBoxAA(location.x - width / 2, location.y - width / 2, location.x + width / 2, location.y + height / 2, 0xffffff, true);
	// 中心座標
	DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);

	// 画像の描画
	if (hp > 0)
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_walk_img[image_num], TRUE, FALSE);
	}
	else
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_death_img[image_num], TRUE, FALSE);
	}
}

// 被ダメージ処理
void Enemy::Damege(int damege)
{
	hp -= (float)damege;
}
