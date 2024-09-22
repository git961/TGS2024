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

	enemy_state = EnemyState::LIVE;

	LoadDivGraph("images/Enemy/Hard.png", 10, 5, 2, 128, 128, enemy_img);

	anim_wait_time = 0;
	delete_wait_time = 120;
}

HardEnemy::~HardEnemy()
{
	// 画像の削除
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(enemy_img[i]);
	}
}

void HardEnemy::Update()
{
	switch (enemy_state)
	{
	case EnemyState::LIVE:
		if (anim_wait_time > 180)
		{
			// 生きているときのアニメーション
			LivingAnimation();
		}
		else
		{
			anim_wait_time++;
		}

		// 死亡状態になったか調べる
		CheckDeathCondition();
		break;


	case EnemyState::DEATH:
		// 死亡処理
		Death();
		DeathAnimation();
		break;

	default:
		break;
	}

	if (star_flg == true)
	{
		StarEffectPreparation();
	}

	// 星を描画するのであれば
	if (star_is_draw == true)
	{
		StarEffect();
	}
}

void HardEnemy::Draw() const
{
	// ダイナマイトでしか倒せない敵の画像
	DrawRotaGraph((int)location.x, (int)location.y, 1.0, 0.0, enemy_img[enemy_img_num], TRUE, direction);

	if (star_is_draw == true)
	{
		// 星描画
		DrawRotaGraph((int)star_x, (int)star_y, 1.0, star_radian, star_img, TRUE, star_direction);
	}

	//DrawFormatString((int)location.x, (int)location.y, 0xffff00, "hp: %.1f", hp);
	//DrawFormatString((int)location.x, (int)location.y, 0xffff00, "anim_cnt: %d", anim_cnt);
}

void HardEnemy::Move()
{

}

void HardEnemy::Death()
{
	if (delete_wait_time > 0)
	{
		delete_wait_time--;
	}
	else
	{
		// 削除
		is_delete = true;
	}
}

void HardEnemy::DeathAnimation()
{
	if (anim_cnt <= 3)
	{
		// アニメーション用カウント増加
		anim_cnt++;
	}
	else
	{
		anim_cnt = 0;

		if (enemy_img_num < 9)
		{
			// 画像切り替え
			enemy_img_num++;
		}
	}
}

// 生きているときのアニメーション
void HardEnemy::LivingAnimation()
{
	if (anim_cnt <= 4)
	{
		// アニメーション用カウント増加
		anim_cnt++;
	}
	else
	{
		anim_cnt = 0;

		// 画像切り替え
		enemy_img_num++;

		// 画像が一通り切り替え終わったら
		if (enemy_img_num > 4)
		{
			enemy_img_num = 0;
			// もう一度待つ
			anim_wait_time = 0;
		}
	}
}

// 死亡状態になったか調べる
void HardEnemy::CheckDeathCondition()
{
	if (hp <= 0.0f)
	{
		anim_cnt = 0;								// 死亡アニメーション用にカウントを0にする
		enemy_img_num = 6;							// 死亡画像の最初の画像番号を設定
		enemy_state = EnemyState::DEATH;			// 死亡状態に遷移
		gem_drop_flg = true;						// 宝石をドロップする
	}
}
