#include "GameClearScene.h"

GameClearScene::GameClearScene()
{
	change_cnt = 180;

	volume = 150;

	// サウンド読込
	gameclear_bgm = LoadSoundMem("sounds/bgm/gamemain.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, gameclear_bgm);

}

GameClearScene::~GameClearScene()
{

}

void GameClearScene::Update()
{
	input.InputUpdate();

	// クリアbgmループ再生
	if (CheckSoundMem(gameclear_bgm) == FALSE)
	{
		PlaySoundMem(gameclear_bgm, DX_PLAYTYPE_LOOP);
	}

	if (change_cnt > 0)
	{
		change_cnt--;
	}
}

void GameClearScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "GameClear");
	DrawFormatString(10, 30, 0xffffff, "B: EndCredits");
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);

#endif // DEBUG

}

AbstractScene* GameClearScene::Change()
{
	if (change_cnt <= 0)
	{
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			// クリアbgm停止
			if (CheckSoundMem(gameclear_bgm) == TRUE)
			{
				StopSoundMem(gameclear_bgm);
			}

			// Bボタンでエンドロールに遷移
			return new EndCreditsScene;
		}
	}
	return this;
}
