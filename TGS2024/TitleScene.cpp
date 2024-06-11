#include "TitleScene.h"

TitleScene::TitleScene()
{
	pickaxe_x = -10.0;
	pickaxe_y = -10.0;
	cursor_x = 400;
	cursor_y = 410;
	degree = 50.0;
	radian = 0.0;
	cursor_start_y = 120;
	cursor_move_interval = 40;
	cursor_num = Start;
	crack_x = 645;
	crack_y = 205;
	distance_x = 0.0;
	distance_y = 0.0;
	distance = 0.0;
	count = 0;
	text_up_flg = true;
	anim_stop_flg = false;

	start_x = 0.0f;
	start_y = 0.0f;
	tmp_sin = 0.0f;
	speed = 5.0;

	start_text_y = 750.0f;
	end_text_y = 860.0f;
	tmp_start_text_y = start_text_y;
	tmp_end_text_y = end_text_y;

	push_b_flg = false;
	scene_change_cnt = 0;
	scene_change_flg = false;

	anim_cnt = 0;
	pickaxe_anim_cnt = 0;
	rock_break_num = 1;
	rock_braek_timer = 250;

	//volume = 150;

	// 画像読込
	back_img = LoadGraph("images/scene/title/title05.png");
	cursor_img = LoadGraph("images/scene/title/cursor.png");
	LoadDivGraph("images/scene/title/pickaxe.png", 3, 3, 1, 170, 170, pickaxe_img);
	text_img[0] = LoadGraph("images/scene/title/gangancrush.png");
	text_img[1] = LoadGraph("images/scene/title/start.png");
	text_img[2] = LoadGraph("images/scene/title/end.png");
	text_img[3] = LoadGraph("images/scene/title/push_b_blue.png");
	rock_break_img[0] = LoadGraph("images/scene/title/rockbreak(kari)1.png");
	rock_break_img[1] = LoadGraph("images/scene/title/rockbreak(kari)3.png");
	rock_break_img[2] = LoadGraph("images/scene/title/rockbreak(kari)4.png");
	rock_break_img[3] = LoadGraph("images/scene/title/rockbreak(kari)5.png");
	rock_break_img[4] = LoadGraph("images/scene/title/rockbreak(kari)6.png");
	rock_break_img[5] = LoadGraph("images/scene/title/rockbreak(kari)7.png");
	rock_break_img[6] = LoadGraph("images/scene/title/rockbreak(kari)8.png");

	pickaxe_img_num = 0;

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
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(pickaxe_img[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		DeleteGraph(rock_break_img[i]);
	}

	// サウンド削除
	DeleteSoundMem(title_bgm);
	DeleteSoundMem(move_cursor_se);
	DeleteSoundMem(decision_se);
}

void TitleScene::Update()
{
	input.InputUpdate();

	//PickaxeAnimation();

	if (anim_cnt < 320)
	{
		anim_cnt++;

		if (anim_cnt >= rock_braek_timer)
		{
			// 岩が崩れるアニメーション
			CrumblingRock();
		}
		else if(anim_cnt >= 60)
		{
			// つるはし回転アニメーション
			PickaxeRotation();
		}
		radian = (double)DEGREE_RADIAN(degree);

	}
	else
	{
		if (text_up_flg == true)
		{
			// テキストが動く際の値の割り当て
			ValueAssignment();
		}

		if (anim_stop_flg == false)
		{
			if (tmp_sin <= 0.9f)
			{
				// テキストを下から上に出す処理
				MoveText();
			}
			else
			{
				// テキスト位置決定処理
				TextPositioning();
			}
		}
		else
		{
			if (cursor_move_interval < 15)
			{
				cursor_move_interval++;
			}
			else
			{
				if (push_b_flg == false)
				{
					// パッド操作
					PadOperation();

					if (cursor_num == Start)
					{
						start_y = 410.0;
					}
					else
					{
						start_y = 520.0;
					}
					pickaxe_y = start_y - sinf(M_PI * 2 / 100 * count) * 10;

					// sin用カウント
					if (count < 100)
					{
						count++;
					}
					else
					{
						count = 0;
					}

				}
				else
				{
					scene_change_cnt++;

					if (scene_change_cnt >= 120)
					{
						// 180fでシーン切り替え
						scene_change_flg = true;
					}

					// つるはしアニメーション
					PickaxeAnimation();
				}
			}
		}
	}

	// タイトルbgmループ再生
	if (CheckSoundMem(title_bgm) == FALSE)
	{
		PlaySoundMem(title_bgm, DX_PLAYTYPE_LOOP);
	}

}

void TitleScene::Draw() const
{
#ifdef DEBUG
	SetFontSize(20);
	DrawFormatString(10, 10, 0xffffff, "Title");
	DrawFormatString(10, 70, 0xffffff, "scene_change_cnt: %d", scene_change_cnt);
	//DrawFormatString(10, 70, 0xffffff, "pickaxe_x: %f", pickaxe_x);
	//DrawFormatString(10, 90, 0xffffff, "pickaxe_y: %f", pickaxe_y);

	//SetFontSize(40);
	//DrawFormatString(150, 130, 0xffffff, "Start");
	//DrawFormatString(150, 250, 0xffffff, "End");

#endif // DEBUG

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	// タイトル配置目安画像
	//DrawRotaGraph(640, 360, 1.0, 0.0, back_img, TRUE, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// タイトル
	DrawRotaGraph(640, 180, 1.0, 0.0, text_img[0], TRUE, FALSE);

	// start・end
	DrawRotaGraph(640, start_text_y, 1.0, 0.0, text_img[1], TRUE, FALSE);
	DrawRotaGraph(640, end_text_y, 1.0, 0.0, text_img[2], TRUE, FALSE);

	if (anim_stop_flg == true)
	{
		// push_b
		DrawRotaGraph(640, 650, 1.0, 0.0, text_img[3], TRUE, FALSE);
	}

	if (text_up_flg == true)
	{
		if (anim_cnt < rock_braek_timer)
		{
			// 崩れる岩画像
			DrawRotaGraph(640, 330, 1.0, 0.0, rock_break_img[0], TRUE, FALSE);
		}
		else
		{
			DrawRotaGraph(640, 330, 1.0, 0.0, rock_break_img[rock_break_num], TRUE, FALSE);
		}
	}

	// カーソル画像
	if (anim_stop_flg == true)
	{
		DrawRotaGraph((int)pickaxe_x, (int)pickaxe_y, 1.0, 0.0, pickaxe_img[pickaxe_img_num], TRUE, FALSE);
	}
	else
	{
		DrawRotaGraph((int)pickaxe_x, (int)pickaxe_y, 1.0, radian, pickaxe_img[0], TRUE, FALSE);
	}

	//DrawRotaGraph((int)pickaxe_x, (int)pickaxe_y, 1.0, radian, cursor_img, TRUE, FALSE);
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

// つるはし回転アニメーション
void TitleScene::PickaxeRotation()
{
	distance_x = crack_x - pickaxe_x;
	distance_y = crack_y - pickaxe_y;

	// 平方根を使って距離を求める
	distance = sqrt(distance_x * distance_x + distance_y * distance_y);

	pickaxe_x += distance_x / distance * 3.5;
	pickaxe_y += distance_y / distance * 3.5;

	start_x = pickaxe_x;
	start_y = pickaxe_y;

	// つるはし時計回り
	if (degree < 360.0)
	{
		degree += 12.0;
	}
	else
	{
		degree = 0.0;
	}
}

// 岩が崩れるアニメーション
void TitleScene::CrumblingRock()
{
	rock_break_num = (anim_cnt - rock_braek_timer) / 7;
	if (rock_break_num > 6)
	{
		rock_break_num = 6;
	}

	if (rock_break_num >= 1)
	{
		// つるはし反時計回り
		if (degree > 0.0)
		{
			degree -= 15;
		}
		else
		{
			degree = 360.0;
		}

		pickaxe_x -= 10.0;

		if (tmp_sin <= 0.9f)
		{
			tmp_sin = sinf(M_PI * 2 / 60 * count);
			pickaxe_y = start_y - tmp_sin * 100;
		}
		else
		{
			pickaxe_y += speed;
			speed += 0.5;
		}

		// sin用カウント
		if (count < 30)
		{
			count++;
		}
		else
		{
			count = 0;
		}
	}
}

// パッド操作
void TitleScene::PadOperation()
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

	// Bボタンで決定
	if (input.CheckBtn(XINPUT_BUTTON_B) == TRUE)
	{
		// 決定se
		PlaySoundMem(decision_se, DX_PLAYTYPE_BACK);

		push_b_flg = true;
	}
}

// テキストが動く際の値の割り当て
void TitleScene::ValueAssignment()
{
	pickaxe_x = 400.0;
	pickaxe_y = 750.0;
	start_y = pickaxe_y;
	count = 0;
	tmp_sin = 0.0f;
	degree = 0.0;
	radian = (double)DEGREE_RADIAN(degree);
	text_up_flg = false;
}

// テキストを下から上に出す処理
void TitleScene::MoveText()
{
	tmp_sin = sinf(M_PI * 2 / 60 * count);
	pickaxe_y = start_y - tmp_sin * 400;
	start_text_y = tmp_start_text_y - tmp_sin * 400;
	end_text_y = tmp_end_text_y - tmp_sin * 400;

	// sin用カウント
	if (count < 60)
	{
		count++;
	}
	else
	{
		count = 0;
	}
}

// テキスト位置決定処理
void TitleScene::TextPositioning()
{
	if (pickaxe_y <= 410.0)
	{
		pickaxe_y += 5.0;
		start_text_y += 5.0;
		end_text_y += 5.0;
	}
	else
	{
		pickaxe_y = 410.0;
		start_text_y = 410.0;
		end_text_y = 520.0;
		anim_stop_flg = true;
	}
}

// つるはしアニメーション
void TitleScene::PickaxeAnimation()
{
	pickaxe_anim_cnt++;

	if (pickaxe_anim_cnt != 0)
	{
		if (pickaxe_img_num < 2)
		{
			pickaxe_img_num = pickaxe_anim_cnt / 3;
		}
	}

	if (pickaxe_anim_cnt >= 60)
	{
		pickaxe_anim_cnt = 0;
	}
}
