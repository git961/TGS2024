#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	change_cnt = 180;

	volume = 150;

	// サウンド読込
	gameover_bgm = LoadSoundMem("sounds/bgm/gamemain.mp3");

	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, gameover_bgm);
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Update()
{
	input.InputUpdate();

	// ゲームオーバーbgmループ再生
	if (CheckSoundMem(gameover_bgm) == FALSE)
	{
		PlaySoundMem(gameover_bgm, DX_PLAYTYPE_LOOP);
	}

	if (change_cnt > 0)
	{
		change_cnt--;
	}
}

void GameOverScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "GameOver");
	DrawFormatString(10, 30, 0xffffff, "B: Title");
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);
#endif // DEBUG

}

AbstractScene* GameOverScene::Change()
{
	if (change_cnt <= 0)
	{
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			// ゲームオーバーbgm停止
			if (CheckSoundMem(gameover_bgm) == TRUE)
			{
				StopSoundMem(gameover_bgm);
			}

			// Bボタンでタイトルに遷移
			return new TitleScene;
		}
	}
	return this;
}
