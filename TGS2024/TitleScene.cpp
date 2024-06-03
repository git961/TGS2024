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

	anim_cnt = 0;

	// 画像読込
	//back_img = LoadGraph("images/Scene/Title/KnockBack.png");
	//cursor_img = LoadGraph("images/Enemy/KnockBack.png");
}

TitleScene::~TitleScene()
{

}

void TitleScene::Update()
{
	input.InputUpdate();

	if (cursor_move_interval < 40)
	{
		cursor_move_interval++;
	}
	else
	{
		if (input.LongPressBtn(XINPUT_BUTTON_DPAD_UP) == TRUE || input.GetPadThumbLY() >= 32000)
		{
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
	}

	if (push_b_flg == false)
	{
		// Bボタンで決定
		if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
		{
			push_b_flg = true;
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

void TitleScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "Title");
	DrawFormatString(10, 30, 0xffffff, "B: decision");

	SetFontSize(40);
	DrawFormatString(150, 130, 0xffffff, "Start");
	DrawFormatString(150, 250, 0xffffff, "End");

	SetFontSize(20);
	DrawFormatString(300, 10, 0xffffff, "scene_change_cnt: %d", scene_change_cnt);
	//DrawFormatString(300, 10, 0xffffff, "cursor_num: %d", cursor_num);
	//DrawFormatString(300, 30, 0xffffff, "cursor_move_interval: %d", cursor_move_interval);
	//DrawFormatString(300, 50, 0xffffff, "Bnum: %d", input.GetBtnnum());
	//DrawFormatString(300, 70, 0xffffff, "BLnum: %d", input.GetLongButtonNum());
	//DrawFormatString(300, 90, 0xffffff, "LPBf: %d", input.GetLongPressBtnflg());
	//DrawFormatString(300, 110, 0xffffff, "LPBU: %d", input.LongPressBtn(XINPUT_BUTTON_DPAD_UP));
	//DrawFormatString(300, 130, 0xffffff, "LPBD: %d", input.LongPressBtn(XINPUT_BUTTON_DPAD_DOWN));
#endif // DEBUG


	DrawCircle(cursor_x, cursor_y * cursor_num + cursor_y, 4, 0xffffff, true);

}

AbstractScene* TitleScene::Change()
{
	if (scene_change_flg == true)
	{
		switch (cursor_num)
		{
		case Start:
			return new AnimScene();
			break;
		case End:
			return new EndScene();
			break;
		default:
			break;
		}
	}
	return this;
}
