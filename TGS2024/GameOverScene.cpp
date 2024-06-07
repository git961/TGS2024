#include "GameOverScene.h"

GameOverScene::GameOverScene(int set_score)
{
	score = set_score;
	change_cnt = 180;
	volume = 150;
	play_sound_flg = true;

	// サウンド読込
	gameover_se = LoadSoundMem("sounds/se/scene/gameover.mp3");

	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, gameover_se);
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Update()
{
	input.InputUpdate();

	// ゲームオーバーse再生
	if (play_sound_flg == true)
	{
		PlaySoundMem(gameover_se, DX_PLAYTYPE_BACK);
		play_sound_flg = false;
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
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);
	DrawFormatString(10, 70, 0xffffff, "score: %d", score);
#endif // DEBUG

	if (change_cnt <= 0)
	{
		DrawFormatString(500, 600, 0xffffff, "B: Title");
	}
}

AbstractScene* GameOverScene::Change()
{
	if (change_cnt <= 0)
	{
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			// ゲームオーバーse停止
			if (CheckSoundMem(gameover_se) == TRUE)
			{
				StopSoundMem(gameover_se);
			}

			// Bボタンでタイトルに遷移
			return new TitleScene;
		}
	}
	return this;
}
