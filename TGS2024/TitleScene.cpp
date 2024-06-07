#include "TitleScene.h"

TitleScene::TitleScene()
{
	cursor_x = 120;
	cursor_y = 120;
	cursor_start_y = 120;
	cursor_move_interval = 40;
	cursor_num = Start;

	push_b_flg = false;
	scene_change_cnt = 0;
	scene_change_flg = false;

	change_cnt = 180;

	anim_cnt = 0;

	//volume = 150;

	// 画像読込
	back_img = LoadGraph("images/scene/title/title05.png");
	cursor_img = LoadGraph("images/scene/title/cursor.png");
	text_img[0] = LoadGraph("images/scene/title/gangancrush.png");
	text_img[1] = LoadGraph("images/scene/title/start.png");
	text_img[2] = LoadGraph("images/scene/title/end.png");
	text_img[3] = LoadGraph("images/scene/title/push_b_blue.png");

	// サウンド読込
	title_bgm = LoadSoundMem("sounds/bgm/title.mp3");
	move_cursor_se = LoadSoundMem("sounds/se/system/cursor.mp3");
	decision_se = LoadSoundMem("sounds/se/player/Attack.mp3");

	// サウンドの音量設定
	ChangeVolumeSoundMem(220, title_bgm);
	ChangeVolumeSoundMem(200, move_cursor_se);
	ChangeVolumeSoundMem(180, decision_se);
}

TitleScene::~TitleScene()
{
	// 画像削除
	DeleteGraph(back_img);
	DeleteGraph(cursor_img);
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(text_img[i]);
	}

	// サウンド削除
	DeleteSoundMem(title_bgm);
	DeleteSoundMem(move_cursor_se);
	DeleteSoundMem(decision_se);
}

void TitleScene::Update()
{
	input.InputUpdate();

	// タイトルbgmループ再生
	if (CheckSoundMem(title_bgm) == FALSE)
	{
		PlaySoundMem(title_bgm, DX_PLAYTYPE_LOOP);
	}

	if (change_cnt > 0)
	{
		change_cnt--;
	}

	if (cursor_move_interval < 15)
	{
		cursor_move_interval++;
	}
	else
	{
		if (push_b_flg == false)
		{
			if (input.LongPressBtn(XINPUT_BUTTON_DPAD_UP) == TRUE || input.GetPadThumbLY() >= 32000)
			{
				// カーソルse
				PlaySoundMem(move_cursor_se, DX_PLAYTYPE_BACK);

				cursor_move_interval = 0;
				// カーソル上移動
				if (cursor_num == Start)
				{
					cursor_num = End;
				}
				else
				{
					cursor_num--;
				}
			}
			if (input.LongPressBtn(XINPUT_BUTTON_DPAD_DOWN) == TRUE || input.GetPadThumbLY() <= -32000)
			{
				// カーソルse
				PlaySoundMem(move_cursor_se, DX_PLAYTYPE_BACK);

				cursor_move_interval = 0;
				// カーソル下移動
				if (cursor_num == End)
				{
					cursor_num = Start;
				}
				else
				{
					cursor_num++;
				}
			}

			if (change_cnt <= 0)
			{
				// Bボタンで決定
				if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
				{
					// 決定se
					PlaySoundMem(decision_se, DX_PLAYTYPE_BACK);

					push_b_flg = true;
				}
			}
		}
		else
		{
			scene_change_cnt++;

			if (scene_change_cnt >= 180)
			{
				// 180fでシーン切り替え
				scene_change_flg = true;
			}
		}
	}

}

void TitleScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "Title");
	DrawFormatString(10, 50, 0xffffff, "draw_cnt: %d", change_cnt);

	SetFontSize(40);
	DrawFormatString(150, 130, 0xffffff, "Start");
	DrawFormatString(150, 250, 0xffffff, "End");

	SetFontSize(20);
	DrawFormatString(300, 10, 0xffffff, "scene_change_cnt: %d", scene_change_cnt);
#endif // DEBUG

	//DrawRotaGraph(640, 360, 1.0, 0.0, back_img, TRUE, FALSE);

	if (change_cnt <= 0)
	{
		DrawFormatString(500, 600, 0xffffff, "B: decision");
	}

	DrawRotaGraph(cursor_x, cursor_y, 1.0, 0.0, cursor_img, TRUE, FALSE);

	DrawCircle(cursor_x, cursor_y * cursor_num + cursor_y, 4, 0xffffff, true);

	// push_b
	DrawRotaGraph(640, 680, 1.0, 0.0, text_img[3], TRUE, FALSE);
}

AbstractScene* TitleScene::Change()
{
	if (scene_change_flg == true)
	{
		switch (cursor_num)
		{
		case Start:
			// タイトルbgm停止
			if (CheckSoundMem(title_bgm) == TRUE)
			{
				StopSoundMem(title_bgm);
			}
			return new AnimScene();
			break;
		case End:
			// タイトルbgm停止
			if (CheckSoundMem(title_bgm) == TRUE)
			{
				StopSoundMem(title_bgm);
			}
			return new EndScene();
			break;
		default:
			break;
		}
	}
	return this;
}
