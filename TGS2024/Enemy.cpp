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
	LoadDivGraph("images/Enemy/EnemyTest.png", 9, 3, 1, 32, 32, chara_image);

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

Enemy::~Enemy()
{
	// 画像の削除
	for (int i = 0; i < 10; i++) {
		DeleteGraph(chara_image[i]);
	}
}

void Enemy::Update(GameMainScene* gamemain)
{
	// 移動処理
	//x += speed * move_x;

	//// 端に来たら跳ね返る、敵同士の当たり判定で使用するかも
	//if (x + width / 2 > 1280 || x - width / 2 < 0)
	//{
	//	move_x *= -1;
	//}

	//if (hp <= 0 && death_cnt != 0)
	//{
	//	death_cnt--;
	//}
}

void Enemy::Draw() const
{
#ifdef DEBUG
	DrawFormatString(0, 50, 0xffffff, "hp : %f", hp);
#endif // DEBUG

	// 当たり判定のボックス
	DrawBoxAA(location.x - width / 2, location.y - width / 2, location.x + width / 2, location.y + height / 2, 0xffffff, true);
	// 中心座標
	DrawCircleAA(location.x, location.y, 1, 0xff00ff, true);

	// 画像の描画
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, chara_image[0], TRUE, FALSE);

	//if (hp <= 0)
	//{
	//	switch (death_cnt)
	//	{
	//	case 80:
	//		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, chara_image[1], TRUE, FALSE);
	//		break;
	//	case 70:
	//		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, chara_image[2], TRUE, FALSE);
	//		break;
	//	case 60:
	//		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, chara_image[3], TRUE, FALSE);
	//		break;
	//	case 50:
	//		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, chara_image[4], TRUE, FALSE);
	//		break;
	//	case 40:
	//		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, chara_image[5], TRUE, FALSE);
	//		break;
	//	case 30:
	//		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, chara_image[6], TRUE, FALSE);
	//		break;
	//	case 20:
	//		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, chara_image[7], TRUE, FALSE);
	//		break;
	//	case 10:
	//		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, chara_image[8], TRUE, FALSE);
	//		break;
	//	default:
	//		break;
	//	}
	//}

}

// 被ダメージ処理
void Enemy::Damege(int damege)
{
	hp -= (float)damege;
}
