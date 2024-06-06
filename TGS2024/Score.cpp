#include "Score.h"

Score::Score()
{
	score_x = 760;			// ウィンドウ幅 / 2 + 画像の幅 * 2 で一の位の表示座標を計算
	score_y = 35;
	score = 0;
	tmp_score = 0;

	for (int i = 0; i < 5; i++)
	{
		num[i] = 0;
	}

	shifting_value = 60;

	//画像読込
	LoadDivGraph("images/UI/num.png", 10, 10, 1, 64, 64, num_img);
}

Score::~Score()
{
	// 画像の削除
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(num_img[i]);
	}
}

void Score::Update()
{
	tmp_score = score;

	for (int i = 0; i < 5; i++)
	{
		if (tmp_score > 0)
		{
			num[i] = tmp_score % 10;
			tmp_score /= 10;
		}
	}
}

void Score::Draw() const
{
	//SetFontSize(20);
	//DrawFormatString(300, 20, 0xffffff, "Score %d", score);

	for (int i = 0; i < 5; i++)
	{
		DrawRotaGraph(score_x - shifting_value * i, score_y, 1.0, 0.0, num_img[num[i]], TRUE, FALSE);
	}
}