#include "EndScene.h"

EndScene::EndScene()
{
	player = new Player(0.0f,600.0f);

	end_cnt = 240;			// 300f経過したら終了
	endflg = false;
	volume = 130;
	se_flg = true;
	// サウンド読込
	end_se = LoadSoundMem("sounds/se/scene/end.mp3");
	// サウンドの音量設定
	ChangeVolumeSoundMem(volume, end_se);

	// 画像の読み込み
	back_img = LoadGraph("images/scene/title/back.png");
	thank_you_img = LoadGraph("images/scene/end/thank_you.png");
}

EndScene::~EndScene()
{
	delete player;

	// 画像削除
	DeleteGraph(back_img);
	DeleteGraph(thank_you_img);

	// サウンド削除
	DeleteSoundMem(end_se);
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

	// プレイヤーアニメーション更新
	player->EndAnimUpdate();
}

void EndScene::Draw() const
{
	//SetFontSize(20);
	//DrawFormatString(10, 10, 0xffffff, "End");
	//DrawFormatString(300, 10, 0xffffff, "end_cnt: %d", end_cnt);

	// 背景画像
	//DrawRotaGraph(640, 360, 1.0, 0.0, back_img, TRUE, FALSE);

	// テキスト画像
	DrawRotaGraph(640, 250, 0.8, 0.0, thank_you_img, TRUE, FALSE);

	// プレイヤー画像
	player->EndAnimDraw();
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
