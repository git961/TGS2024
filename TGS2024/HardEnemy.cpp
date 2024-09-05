#include "HardEnemy.h"

HardEnemy::HardEnemy(float set_x, float set_y)
{
	// 中心座標
	world.x = set_x - 32.0f;
	world.y = set_y - 32.0f;
	location.x = set_x;
	location.y = set_y;
	width = 128.0f;
	height = 128.0f;

	hp = 30.0f;
	direction = false;

	LoadDivGraph("images/Enemy/Hard.png", 6, 5, 2, 128, 128, enemy_img);

	anim_wait_time = 0;
}

HardEnemy::~HardEnemy()
{
	// 画像の削除
	for (int i = 0; i < 6; i++)
	{
		DeleteGraph(enemy_img[i]);
	}
}

void HardEnemy::Update()
{
	if (hp <= 0.0f)
	{
		// 死亡処理
		Death();
		DeathAnimation();
	}
	else
	{
		if (anim_wait_time > 180)
		{
			// 生きているときのアニメーション
			LivingAnimation();
		}
		else
		{
			anim_wait_time++;
		}
	}
}

void HardEnemy::Draw() const
{
	// ダイナマイトでしか倒せない敵の画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img[enemy_img_num], TRUE, direction);

	DrawFormatString((int)location.x, (int)location.y, 0xffff00, "hp: %.1f", hp);
	//DrawFormatString((int)location.x, (int)location.y, 0xffff00, "anim_cnt: %d", anim_cnt);
}

void HardEnemy::Move()
{

}

void HardEnemy::Death()
{
	if (anim_cnt <= 120)
	{
		anim_cnt++;
	}
	else
	{
		// 削除
		is_delete = true;
	}
}

void HardEnemy::DeathAnimation()
{
	enemy_img_num = 5;
}

// 生きているときのアニメーション
void HardEnemy::LivingAnimation()
{
	if (anim_cnt <= 4)
	{
		anim_cnt++;
	}
	else
	{
		anim_cnt = 0;

		enemy_img_num++;
		if (enemy_img_num > 4)
		{
			enemy_img_num = 0;
			anim_wait_time = 0;
		}
	}
}
