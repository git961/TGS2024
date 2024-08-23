#include "Rock.h"
#include <time.h>

Rock::Rock(float set_x, float set_y)
{
	LoadDivGraph("images/Stage/rock.png", 7, 7, 1, 64, 64, rock_img);
	LoadDivGraph("images/Stage/rockeffect.png", 3, 3, 1, 128, 64, rock_effect_img);
	
	world.x = set_x;
	world.y = set_y;
	location.x = world.x;
	location.y = world.y;
	height = 64.0f;
	width = 64.0f;
	hp = 30;
	shake_cnt = 0;
	shakex = 0;
	shake_flg = false;
	rock_num = 0;
	rock_effect_num = 0;
	delete_flg = false;
	delete_cnt = 0;

	LoadDivGraph("images/Stage/fragment.png", 4, 4, 1, 64, 64, fragment_img);

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
	effect_flg = false;

}

Rock::~Rock()
{
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(rock_img[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(rock_effect_img[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(fragment_img[i]);
	}
}

void Rock::Update()
{
	// box_vertexの値を更新し続ける
	SetVertex();

	if (shake_flg == true)
	{
		shake_cnt++;
		switch (shake_cnt)
		{
		case 1:
			effect_flg = true;
			FragmentSet();
			shakex = -5;
			if (hp > 0) {
				rock_num++;
			}
			break;
		case 3:
			shakex = 5;
			break;
		case 10:
			shake_cnt = 0;

			shake_flg = false;
			break;
		default:
			shakex = 0;
			break;
		}
		world.x += shakex;

	}

	if (effect_flg == true)
	{
		FragmentEffect();
	}

	if (hp <= 0) {

		switch (delete_cnt)
		{
		case 0:
			rock_num++;
			break;
		case 3:
			rock_effect_num++;
			rock_num++;
			break;
		case 9:
			rock_effect_num++;
			rock_num++;
			break;
		case 15:
			rock_effect_num++;
			rock_num++;
			break;
		case 18:
			delete_flg = true;
			break;
		}
		delete_cnt++;
	}
	

}

void Rock::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, rock_img[rock_num], TRUE, 0);
	if (rock_num >= 3)
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, rock_effect_img[rock_effect_num], TRUE, 0);
	}
	if (shake_flg == true)
	{
		for (int i = 0; i < 4; i++)
		{
			// 破片描画
			DrawRotaGraph((int)fragment[i].x, (int)fragment[i].y, 1.0, 0.0, fragment_img[i], TRUE, 0);
		}
	}
}


// 石の破片エフェクトの処理
void Rock::FragmentEffect()
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
			fragment[i].y = location.y - height / 2;				// 画像の中心


		}

		start_x = location.x;
		start_y = location.y - height / 2;				// 画像の中心

		if (fragment[i].y < 608.f)
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

		if (fragment[i].is_draw == false)
		{
			fragment[i].is_draw = true;
		}
	}


	if (fragment[0].y == 608.0f && fragment[1].y == 608.0f && fragment[2].y == 608.0f && fragment[3].y == 608.0f)
	{
		effect_flg = false;
		if (hp < 0)
		{
			// 宝石を落とす
			//gem_drop = true;
		}
	}
}

void Rock::FragmentSet()
{
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
}
