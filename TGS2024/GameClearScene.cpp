#include "GameClearScene.h"

GameClearScene::GameClearScene(int set_score)
{
	score = set_score;
	change_cnt = 180;
	volume = 150;
	se_flg = true;

	// サウンド読込
	gameclear_se = LoadSoundMem("sounds/se/scene/gameclear.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, gameclear_se);

}

GameClearScene::~GameClearScene()
{

}

void GameClearScene::Update()
{
	input.InputUpdate();

	// クリアse再生
	if (se_flg == true)
	{
		PlaySoundMem(gameclear_se, DX_PLAYTYPE_BACK);
		se_flg = false;
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
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);
	DrawFormatString(10, 70, 0xffffff, "score: %d", score);

#endif // DEBUG
	if (change_cnt <= 0)
	{
		DrawFormatString(500, 600, 0xffffff, "B: EndCredits");
	}

}

AbstractScene* GameClearScene::Change()
{
	if (change_cnt <= 0)
	{
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			// クリアbgm停止
			if (CheckSoundMem(gameclear_se) == TRUE)
			{
				StopSoundMem(gameclear_se);
			}

			// Bボタンでエンドロールに遷移
			return new EndCreditsScene(score);
		}
	}
	return this;
}
