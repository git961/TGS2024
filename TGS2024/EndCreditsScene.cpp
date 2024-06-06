#include "EndCreditsScene.h"

EndCreditsScene::EndCreditsScene()
{
	change_cnt = 180;
	volume = 30;

	// サウンド読込
	credits_bgm = LoadSoundMem("sounds/bgm/ending.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, credits_bgm);

}

EndCreditsScene::~EndCreditsScene()
{

}

void EndCreditsScene::Update()
{
	input.InputUpdate();

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
#endif // DEBUG

	if (change_cnt <= 0)
	{
		DrawFormatString(500, 600, 0xffffff, "B: Title");
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
