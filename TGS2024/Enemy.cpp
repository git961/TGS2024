#include "Enemy.h"

Enemy::Enemy(float set_x)
{
	// 中心座標
	//location.x = 400 + (40 * set_x);
	//location.y = 600;

	world.x = 400 + (120 * set_x);
	world.y = 600;

	width = 45;
	height = 64;

	move_x = 1;			// 移動量
	move_y = 0;			// 未使用
	hp = 10;
	attack = 10;
	speed = 2;			// なくても良い


	//画像読込
	//LoadDivGraph("images/Enemy/EnemyTest01.png", 9, 3, 1, 64, 64, chara_image);
	LoadDivGraph("images/Enemy/WalkTest.png", 5, 5, 1, 64, 64, enemy_walk_img);
	LoadDivGraph("images/Enemy/WalkDeathTest.png", 4, 4, 1, 64, 64, enemy_death_img);

	anim_cnt = 0;
	anim_max_cnt = 19;

	// 現在の画像
	//image = 0;
	decrease = false;
	image_num = 0;

	death_cnt = 0;
	is_delete = false;

	direction = false;		// 画像は右向き

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
			if (anim_cnt < anim_max_cnt)
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
			// 60カウント以上なら削除フラグをtrueに変更
			is_delete = true;
		}
	}

	// 画像切り替え
	if (hp > 0)
	{
		if (anim_cnt != 0)
		{	
			// 歩行
			// 20カウントごとに変わる
			image_num = anim_cnt / 5;
		}
	}
	else
	{
		if (death_cnt != 0)
		{
			// 死亡
			// 5カウントごとに変わる
			image_num = death_cnt / 5;
		}

		if (image_num > 3)
		{
			// 最終画像で止める
			image_num = 3;
		}
	}

	if (hp > 0)
	{
		// 端に来たら跳ね返る、敵同士の当たり判定で使用するかも
		if (world.x + width / 2 > FIELD_WIDTH || world.x - width / 2 < 0)
		{

			//ChangeDirection();
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

		// 移動処理
		world.x -= speed * move_x;
	}
}

void Enemy::Draw() const
{
#ifdef DEBUG
	//DrawFormatString(0, 50, 0xffffff, "death_cnt : %d", death_cnt);
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

// 被ダメージ処理
void Enemy::Damege(int damege)
{
	hp -= (float)damege;
}
