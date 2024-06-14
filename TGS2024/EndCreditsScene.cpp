#include "EndCreditsScene.h"

EndCreditsScene::EndCreditsScene(int set_score)
{
	text_x = 700;
	text_y = 720;
	timer = 0;
	score = set_score;
	tmp_score = score;
	for (int i = 0; i < 5; i++)
	{
		num[i] = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		if (tmp_score > 0)
		{
			num[i] = tmp_score % 10;
			tmp_score /= 10;
		}
	}

	change_cnt = 180;
	volume = 20;
	volume_timer = 1;

	// 画像読込
	text_img[0] = LoadGraph("images/scene/credit/materials_used.png");
	text_img[1] = LoadGraph("images/scene/credit/bgm_se.png");
	text_img[2] = LoadGraph("images/scene/credit/koukaonrabo.png");
	text_img[3] = LoadGraph("images/scene/credit/koukaonkoubou.png");
	text_img[4] = LoadGraph("images/scene/credit/maoudamasii.png");
	text_img[5] = LoadGraph("images/scene/credit/otologic.png");
	text_img[6] = LoadGraph("images/scene/credit/image.png");
	text_img[7] = LoadGraph("images/scene/credit/dotlist.png");
	text_img[8] = LoadGraph("images/scene/credit/font.png");
	text_img[9] = LoadGraph("images/scene/credit/4_4gokusyoukanafont.png");
	text_img[10] = LoadGraph("images/scene/credit/pixelmplus10.png");
	text_img[11] = LoadGraph("images/scene/credit/your_score.png");
	text_img[12] = LoadGraph("images/scene/credit/dova_sindrome.png");
	LoadDivGraph("images/scene/credit/num.png", 10, 10, 1, 64, 64, num_img);
	push_b_img = LoadGraph("images/scene/push_b_white.png");

	// サウンド読込
	credits_bgm = LoadSoundMem("sounds/bgm/ending.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, credits_bgm);

}

EndCreditsScene::~EndCreditsScene()
{
	// 画像削除
	for (int i = 0; i < 12; i++)
	{
		DeleteGraph(text_img[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(num_img[i]);
	}
	DeleteGraph(push_b_img);

	// サウンド削除
	DeleteSoundMem(credits_bgm);
}

void EndCreditsScene::Update()
{
	input.InputUpdate();

	if (timer < 2500)
	{
		timer++;
	}
	else
	{
		if (change_cnt > 0)
		{
			change_cnt--;
		}
	}

	// クレジットbgmループ再生
	if (CheckSoundMem(credits_bgm) == FALSE)
	{
		PlaySoundMem(credits_bgm, DX_PLAYTYPE_LOOP);
	}

	if (volume < 140)
	{
		volume_timer++;
		if (volume_timer % 2 == 0)
		{
			volume++;
			ChangeVolumeSoundMem(volume, credits_bgm);
		}
	}
}

void EndCreditsScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "EndCredits");
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);
	DrawFormatString(10, 70, 0xffffff, "volume: %d", volume);
	DrawFormatString(10, 90, 0xffffff, "score: %d", score);
#endif // DEBUG

	// 使用素材
	DrawRotaGraph(640, 800 - timer, 1.0, 0.0, text_img[0], TRUE, FALSE);

	// bgm・seなど
	DrawRotaGraph(640, 950 - timer, 1.0, 0.0, text_img[1], TRUE, FALSE);
	DrawRotaGraph(640, 1030 - timer, 1.0, 0.0, text_img[2], TRUE, FALSE);
	DrawRotaGraph(640, 1110 - timer, 1.0, 0.0, text_img[3], TRUE, FALSE);
	DrawRotaGraph(640, 1190 - timer, 1.0, 0.0, text_img[4], TRUE, FALSE);
	DrawRotaGraph(640, 1270 - timer, 1.0, 0.0, text_img[5], TRUE, FALSE);
	DrawRotaGraph(640, 1350 - timer, 1.0, 0.0, text_img[12], TRUE, FALSE);

	// 画像など
	DrawRotaGraph(640, 1500 - timer, 1.0, 0.0, text_img[6], TRUE, FALSE);
	DrawRotaGraph(640, 1580 - timer, 1.0, 0.0, text_img[7], TRUE, FALSE);

	// フォントなど
	DrawRotaGraph(640, 1730 - timer, 1.0, 0.0, text_img[8], TRUE, FALSE);
	DrawRotaGraph(640, 1810 - timer, 1.0, 0.0, text_img[9], TRUE, FALSE);
	DrawRotaGraph(640, 1890 - timer, 1.0, 0.0, text_img[10], TRUE, FALSE);

	// スコア
	DrawRotaGraph(650, 2670 - timer, 1.0, 0.0, text_img[11], TRUE, FALSE);
	for (int i = 0; i < 5; i++)
	{
		DrawRotaGraph(860 - 110 * i, 2870 - timer, 2.0, 0.0, num_img[num[i]], TRUE, FALSE);
	}

	if (change_cnt <= 0)
	{
		DrawRotaGraph(640, 600, 1.0, 0.0, push_b_img, TRUE, FALSE);
	}
}

AbstractScene* EndCreditsScene::Change()
{
	if (change_cnt <= 0)
	{
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			// クレジットbgm停止
			if (CheckSoundMem(credits_bgm) == TRUE)
			{
				StopSoundMem(credits_bgm);
			}

			// Bボタンでタイトルに遷移
			return new TitleScene();
		}
	}

	return this;
}
