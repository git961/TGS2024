#include "Enemy.h"

Enemy::Enemy(float set_x)
{
	// 中心座標
	//location.x = 400 + (40 * set_x);
	//location.y = 600;

	world.x = 400 + (40 * set_x);
	world.y = 600;

	width = 30;
	height = 30;

	move_x = 1;			// 移動量
	move_y = 0;			// 未使用
	hp = 10;
	attack = 10;
	speed = 3;			// なくても良い


	//画像読込
	//LoadDivGraph("images/Enemy/EnemyTest01.png", 9, 3, 1, 64, 64, chara_image);
	LoadDivGraph("images/Enemy/EnemyTest_walk.png", 3, 3, 1, 32, 32, enemy_walk_img);
	LoadDivGraph("images/Enemy/EnemyTest_death.png", 6, 6, 1, 32, 32, enemy_death_img);

	anim_cnt = 0;
	// 現在の画像
	//image = 0;
	decrease = false;
	image_num = 0;

	death_cnt = 0;

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
			if (anim_cnt < 59)
			{
				// アニメーション用カウント増加
				anim_cnt++;
			}
			else
			{
				decrease = true;
			}
		}
		else
		{
			if (anim_cnt > 0)
			{
				// アニメーション用カウント減少
				anim_cnt--;
			}
			else
			{
				decrease = false;
			}
		}
	}
	else
	{
		//if (death_cnt > 0)
		//{
			death_cnt++;
		//}
	}

	// 画像切り替え
	if (hp > 0)
	{
		if (anim_cnt != 0)
		{	
			// 20カウントごとに変わる
			image_num = anim_cnt / 20;
		}

		// 歩行アニメーション（仮）
		//if (anim_cnt <= 20)
		//{
		//	image = chara_image[0];
		//}
		//else if (anim_cnt <= 40)
		//{
		//	image = chara_image[1];
		//}
		//else if (anim_cnt <= 60)
		//{
		//	image = chara_image[2];
		//}
	}
	else
	{
		if (death_cnt != 0)
		{
			image_num = death_cnt / 10;
		}

		// 死亡アニメーション（仮）
		//if (death_cnt >= 50)
		//{
		//	image = chara_image[3];
		//}
		//else if (death_cnt >= 40)
		//{
		//	image = chara_image[4];
		//}
		//else if (death_cnt >= 30)
		//{
		//	image = chara_image[5];
		//}
		//else if (death_cnt >= 20)
		//{
		//	image = chara_image[6];
		//}
		//else if (death_cnt >= 10)
		//{
		//	image = chara_image[7];
		//}
		//else if (death_cnt >= 0)
		//{
		//	image = chara_image[8];
		//}
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


	//if (hp <= 0 && death_cnt != 0)
	//{
	//	death_cnt--;
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
	DrawBoxAA(location.x - width / 2, location.y - width / 2, location.x + width / 2, location.y + height / 2, 0xffffff, true);
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
