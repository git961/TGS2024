#include "EndScene.h"

EndScene::EndScene()
{
	end_cnt = 300;			// 300f経過したら終了
	endflg = false;
	fps = 0;
	volume = 150;

	// サウンド読込
	end_bgm = LoadSoundMem("sounds/bgm/gamemain.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, end_bgm);

}

EndScene::~EndScene()
{

}

void EndScene::Update()
{
	end_cnt--;

	// エンドbgmループ再生
	if (CheckSoundMem(end_bgm) == FALSE)
	{
		PlaySoundMem(end_bgm, DX_PLAYTYPE_LOOP);
	}

	if (end_cnt != 0)
	{
		if (end_cnt % 60 == 0)
		{
			fps++;
		}
	}
	if (end_cnt <= 0)
	{
		endflg = true;
	}
}

void EndScene::Draw() const
{
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "End");
	DrawFormatString(300, 10, 0xffffff, "end_cnt: %d", end_cnt);
	DrawFormatString(300, 30, 0xffffff, "fps: %d", fps);

}

AbstractScene* EndScene::Change()
{
	if (endflg == true)
	{
		// エンドbgm停止
		if (CheckSoundMem(end_bgm) == TRUE)
		{
			StopSoundMem(end_bgm);
		}

		// 終了
		return nullptr;
	}

	return this;
}
