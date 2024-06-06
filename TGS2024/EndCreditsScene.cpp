#include "EndCreditsScene.h"

EndCreditsScene::EndCreditsScene()
{
	text_x = 700;
	text_y = 720;
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

	SetFontSize(40);

	// テキストは画像に変更する
	DrawFormatString(500, 100, 0xffffff, "1");

	DrawFormatString(500, 150, 0xffffff, "2");
	DrawFormatString(500, 190, 0xffffff, "3");
	DrawFormatString(500, 230, 0xffffff, "4");
	DrawFormatString(500, 270, 0xffffff, "5");
	DrawFormatString(500, 310, 0xffffff, "6");

	DrawFormatString(500, 360, 0xffffff, "7");
	DrawFormatString(500, 400, 0xffffff, "8");

	DrawFormatString(500, 450, 0xffffff, "9");
	DrawFormatString(500, 490, 0xffffff, "10");

	// ↓文字化けする
	//DrawFormatString(500, 100, 0xffffff, "使用素材");

	//DrawFormatString(500, 150, 0xffffff, "BGM・SE");
	//DrawFormatString(500, 190, 0xffffff, "効果音ラボ");
	//DrawFormatString(500, 230, 0xffffff, "効果音工房");
	//DrawFormatString(500, 270, 0xffffff, "魔王魂");
	//DrawFormatString(500, 310, 0xffffff, "OtoLogic");

	//DrawFormatString(500, 360, 0xffffff, "画像");
	//DrawFormatString(500, 400, 0xffffff, "DOTLIST");

	//DrawFormatString(500, 450, 0xffffff, "フォント");
	//DrawFormatString(500, 490, 0xffffff, "4x4極小かなフォント");

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
