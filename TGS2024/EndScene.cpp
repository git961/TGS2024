#include "EndScene.h"

EndScene::EndScene()
{
	end_cnt = 240;			// 300f経過したら終了
	endflg = false;
	volume = 150;
	se_flg = true;
	// サウンド読込
	end_se = LoadSoundMem("sounds/se/scene/end02.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, end_se);

}

EndScene::~EndScene()
{

}

void EndScene::Update()
{
	end_cnt--;

	if (end_cnt <= 180)
	{
		// エンドse再生
		if (se_flg == true)
		{
			PlaySoundMem(end_se, DX_PLAYTYPE_BACK);
			se_flg = false;
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

}

AbstractScene* EndScene::Change()
{
	if (endflg == true)
	{
		// エンドse停止
		if (CheckSoundMem(end_se) == TRUE)
		{
			StopSoundMem(end_se);
		}

		// 終了
		return nullptr;
	}

	return this;
}
