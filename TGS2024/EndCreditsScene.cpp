#include "EndCreditsScene.h"

EndCreditsScene::EndCreditsScene(int set_score)
{
	text_x = 700;
	text_y = 720;
	timer = 0;
	score = set_score;
	change_cnt = 180;
	volume = 30;

	// 画像読込
	text_img[0] = LoadGraph("images/text/credit/materials_used.png");
	text_img[1] = LoadGraph("images/text/credit/bgm_se.png");
	text_img[2] = LoadGraph("images/text/credit/koukaonrabo.png");
	text_img[3] = LoadGraph("images/text/credit/koukaonkoubou.png");
	text_img[4] = LoadGraph("images/text/credit/maoudamasii.png");
	text_img[5] = LoadGraph("images/text/credit/otologic.png");
	text_img[6] = LoadGraph("images/text/credit/image.png");
	text_img[7] = LoadGraph("images/text/credit/dotlist.png");
	text_img[8] = LoadGraph("images/text/credit/font.png");
	text_img[9] = LoadGraph("images/text/credit/4_4gokusyoukanafont.png");
	text_img[10] = LoadGraph("images/text/credit/pixelmplus10.png");
	text_img[11] = LoadGraph("images/text/credit/your_score.png");
	LoadDivGraph("images/UI/num.png", 10, 10, 1, 64, 64, num_img);

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

	// サウンド削除
	DeleteSoundMem(credits_bgm);
}

void EndCreditsScene::Update()
{
	input.InputUpdate();

	timer++;

	// クレジットbgmループ再生
	if (CheckSoundMem(credits_bgm) == FALSE)
	{
		PlaySoundMem(credits_bgm, DX_PLAYTYPE_LOOP);
	}

	if (volume < 140)
	{
		volume++;
		ChangeVolumeSoundMem(volume, credits_bgm);
	}

	if (change_cnt > 0)
	{
		change_cnt--;
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

	if (change_cnt <= 0)
	{
		DrawFormatString(500, 600, 0xffffff, "B: Title");
	}

	// 使用素材
	DrawRotaGraph(640, 800 - timer, 1.0, 0.0, text_img[0], TRUE, FALSE);

	// bgm・seなど
	DrawRotaGraph(640, 950 - timer, 1.0, 0.0, text_img[1], TRUE, FALSE);
	DrawRotaGraph(640, 1030 - timer, 1.0, 0.0, text_img[2], TRUE, FALSE);
	DrawRotaGraph(640, 1110 - timer, 1.0, 0.0, text_img[3], TRUE, FALSE);
	DrawRotaGraph(640, 1190 - timer, 1.0, 0.0, text_img[4], TRUE, FALSE);
	DrawRotaGraph(640, 1270 - timer, 1.0, 0.0, text_img[5], TRUE, FALSE);

	// 画像など
	DrawRotaGraph(640, 1420 - timer, 1.0, 0.0, text_img[6], TRUE, FALSE);
	DrawRotaGraph(640, 1500 - timer, 1.0, 0.0, text_img[7], TRUE, FALSE);

	// フォントなど
	DrawRotaGraph(640, 1650 - timer, 1.0, 0.0, text_img[8], TRUE, FALSE);
	DrawRotaGraph(640, 1730 - timer, 1.0, 0.0, text_img[9], TRUE, FALSE);
	DrawRotaGraph(640, 1810 - timer, 1.0, 0.0, text_img[10], TRUE, FALSE);

	// スコア
	DrawRotaGraph(640, 2500 - timer, 1.0, 0.0, text_img[11], TRUE, FALSE);

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
