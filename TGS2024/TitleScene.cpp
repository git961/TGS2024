#include "TitleScene.h"

TitleScene::TitleScene()
{
	pickaxe_x = -10.0;
	pickaxe_y = -10.0;
	cursor_x = 400;
	cursor_y = 410;
	degree = 50.0;
	radian = 0.0;
	rock_degree = 0.0;
	rock_radian = 0.0;
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
	crack_rock_flg = false;

	start_x = 0.0f;
	start_y = 0.0f;
	tmp_sin = 0.0f;
	speed = 5.0;

	start_text_y = 760.0f;
	end_text_y = 870.0f;
	tmp_start_text_y = start_text_y;
	tmp_end_text_y = end_text_y;

	sparkling_size = 0.0;	
	sparkling_degree = 0.0;
	sparkling_radian = 0.0;
	sparkling_anim_cnt = 0;

	push_b_flg = false;
	scene_change_cnt = 90;
	scene_change_flg = false;

	anim_cnt = 0;
	pickaxe_anim_cnt = 0;
	rock_break_num = 1;
	rock_img_num = 0;
	rock_braek_timer = 250;

	move_x = 0;
	move_y = 0;
	fragment_anim_cnt = 0;
	draw_cursor_flg = false;

	//volume = 150;

	// 画像読込
	back_img = LoadGraph("images/scene/title/back.png");
	pickaxe_img = LoadGraph("images/scene/title/pickaxe01.png");
	LoadDivGraph("images/scene/title/cursor01.png", 3, 3, 1, 128, 92, cursor_img);
	text_img[0] = LoadGraph("images/scene/title/title.png");
	text_img[1] = LoadGraph("images/scene/title/start.png");
	text_img[2] = LoadGraph("images/scene/title/end.png");
	text_img[3] = LoadGraph("images/scene/title/push_b_blue.png");
	LoadDivGraph("images/scene/title/TitleRockAnim01.png", 3, 1, 3, 850, 320, rock_img);
	LoadDivGraph("images/scene/title/TitleRocks01.png", 10, 10, 1, 430, 320, rock_fragments_img);
	sparkling_img = LoadGraph("images/scene/title/sparkling.png");

	pickaxe_img_num = 0;

	// サウンド読込
	title_bgm = LoadSoundMem("sounds/bgm/title.mp3");
	move_cursor_se = LoadSoundMem("sounds/se/scene/title/cursor.mp3");
	decision_se = LoadSoundMem("sounds/se/player/Attack.mp3");
	collapse_se = LoadSoundMem("sounds/se/scene/title/collapse.mp3");
	crack_se = LoadSoundMem("sounds/se/scene/title/crack.mp3");
	swing_se = LoadSoundMem("sounds/se/scene/title/swing.mp3");

	// サウンドの音量設定
	ChangeVolumeSoundMem(220, title_bgm);
	ChangeVolumeSoundMem(200, move_cursor_se);
	ChangeVolumeSoundMem(180, decision_se);
	ChangeVolumeSoundMem(220, collapse_se);
	ChangeVolumeSoundMem(190, crack_se);
	ChangeVolumeSoundMem(190, swing_se);

	swing_se_cnt = 0;
}

TitleScene::~TitleScene()
{
	// 画像削除
	DeleteGraph(back_img);
	DeleteGraph(pickaxe_img);
	DeleteGraph(sparkling_img);
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(text_img[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(cursor_img[i]);
		DeleteGraph(rock_img[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(rock_fragments_img[i]);
	}

	// サウンド削除
	DeleteSoundMem(title_bgm);
	DeleteSoundMem(move_cursor_se);
	DeleteSoundMem(decision_se);
	DeleteSoundMem(collapse_se);
	DeleteSoundMem(crack_se);
	DeleteSoundMem(swing_se);
}

void TitleScene::Update()
{
	input.InputUpdate();

	if (anim_cnt < 320)
	{
		anim_cnt++;

		if (anim_cnt >= rock_braek_timer)
		{
			if (crack_rock_flg == false)
			{
				// 岩が入るアニメーション
				CrackRock();
			}
			else
			{
				if (fragment_anim_cnt < 7)
				{
					fragment_anim_cnt++;
				}
				else
				{
					// 岩が崩れるアニメーション
					RockCollapses();
				}
			}

			// つるはし落下アニメーション
			PickaxeFalling();
		}
		else if(anim_cnt >= 60)
		{
			// つるはし回転アニメーション
			PickaxeRotation();
		}

		// 角度をデグリーからラジアンへ変換
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
			if (draw_cursor_flg == false)
			{
				draw_cursor_flg = true;
			}

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
					pickaxe_y = start_y - sinf((float)M_PI * 2.0f / 100.f * (float)count) * 10.0f;

					// sin用カウント
					if (count < 100)
					{
						count++;
					}
					else
					{
						count = 0;
					}

					// きらきらアニメーション
					SparklingAnimation();
				}
				else
				{
					scene_change_cnt--;

					if (scene_change_cnt <= 0)
					{
						// 90fでシーン切り替え
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
	//SetFontSize(20);

	//DrawFormatString(10, 10, 0xffffff, "Title");
	//DrawFormatString(10, 70, 0xffffff, "scene_change_cnt: %d", scene_change_cnt);
	//DrawFormatString(10, 70, 0xffffff, "pickaxe_x: %f", pickaxe_x);
	//DrawFormatString(10, 90, 0xffffff, "pickaxe_y: %f", pickaxe_y);

	//SetFontSize(40);
	//DrawFormatString(150, 130, 0xffffff, "Start");
	//DrawFormatString(150, 250, 0xffffff, "End");

#endif // DEBUG

	// 背景画像
	DrawRotaGraph(640, 360, 1.0, 0.0, back_img, TRUE, FALSE);

	// タイトル
	DrawRotaGraph(640, 180, 1.0, 0.0, text_img[0], TRUE, FALSE);

	// start・end
	DrawRotaGraph(640, (int)start_text_y, 1.0, 0.0, text_img[1], TRUE, FALSE);
	DrawRotaGraph(640, (int)end_text_y, 1.0, 0.0, text_img[2], TRUE, FALSE);

	if (anim_stop_flg == true)
	{
		// push_b
		DrawRotaGraph(640, 650, 1.0, 0.0, text_img[3], TRUE, FALSE);
	}

	if (text_up_flg == true)
	{
		if (crack_rock_flg == false)
		{
			DrawRotaGraph(640, 170, 1.0, 0.0, rock_img[rock_img_num], TRUE, FALSE);
		}
		else
		{
			if (fragment_anim_cnt < 7)
			{
				// 岩の破片画像
				DrawRotaGraph(950 + move_x, 270 + move_y, 1.0, 0.0, rock_fragments_img[0], TRUE, FALSE);
				DrawRotaGraph(930 + move_x, 120 + move_y, 1.0, 0.0, rock_fragments_img[1], TRUE, FALSE);
				DrawRotaGraph(940 + move_x, 50 + move_y, 1.0, 0.0, rock_fragments_img[2], TRUE, FALSE);
				DrawRotaGraph(720, 90 + move_y, 1.0, 0.0, rock_fragments_img[3], TRUE, FALSE);
				DrawRotaGraph(780, 200 + move_y, 1.0, 0.0, rock_fragments_img[4], TRUE, FALSE);
				DrawRotaGraph(690, 280 + move_y, 1.0, 0.0, rock_fragments_img[5], TRUE, FALSE);
				DrawRotaGraph(570, 200 + move_y, 1.0, 0.0, rock_fragments_img[6], TRUE, FALSE);
				DrawRotaGraph(470 - move_x, 70 + move_y, 1.0, 0.0, rock_fragments_img[7], TRUE, FALSE);
				DrawRotaGraph(330 - move_x, 140 + move_y, 1.0, 0.0, rock_fragments_img[8], TRUE, FALSE);
				DrawRotaGraph(360 - move_x, 270 + move_y, 1.0, 0.0, rock_fragments_img[9], TRUE, FALSE);
			}
			else
			{
				// 岩回転、x移動あり
				// 岩の破片右側、下から順
				DrawRotaGraph(1000, 300 + move_y, 1.0, (double)DEGREE_RADIAN(20.0 + rock_degree), rock_fragments_img[0], TRUE, FALSE);
				DrawRotaGraph(950, 160 + move_y, 1.0, (double)DEGREE_RADIAN(0.0), rock_fragments_img[1], TRUE, FALSE);
				DrawRotaGraph(970 + move_x, 50 + move_y, 1.0, (double)DEGREE_RADIAN(40.0), rock_fragments_img[2], TRUE, FALSE);

				DrawRotaGraph(720, 60 + move_y, 1.0, (double)DEGREE_RADIAN(0.0), rock_fragments_img[3], TRUE, FALSE);
				DrawRotaGraph(740, 200 + move_y, 1.0, (double)DEGREE_RADIAN(0.0), rock_fragments_img[4], TRUE, FALSE);
				DrawRotaGraph(720, 330 + move_y, 1.0, (double)DEGREE_RADIAN(rock_degree), rock_fragments_img[5], TRUE, FALSE);
				DrawRotaGraph(550, 240 + move_y, 1.0, (double)DEGREE_RADIAN(50.0), rock_fragments_img[6], TRUE, FALSE);

				// 岩の破片左側、上から順
				DrawRotaGraph(450, 60 + move_y, 1.0, (double)DEGREE_RADIAN(350.0 - rock_degree), rock_fragments_img[7], TRUE, FALSE);
				DrawRotaGraph(290, 180 + move_y, 1.0, (double)DEGREE_RADIAN(320.0), rock_fragments_img[8], TRUE, FALSE);
				DrawRotaGraph(300 - move_x, 310 + move_y, 1.0, (double)DEGREE_RADIAN(340.0), rock_fragments_img[9], TRUE, FALSE);
			}
		}
	}

	if (draw_cursor_flg == true)
	{
		// カーソル画像
		DrawRotaGraph((int)pickaxe_x, (int)pickaxe_y, 1.2, 0.0, cursor_img[pickaxe_img_num], TRUE, FALSE);
		
		// キラキラ画像
		DrawRotaGraph(100, 100, sparkling_size, sparkling_radian, sparkling_img, TRUE, FALSE);
		DrawRotaGraph(240, 250, sparkling_size, sparkling_radian, sparkling_img, TRUE, FALSE);
		DrawRotaGraph(400, 520, sparkling_size, sparkling_radian, sparkling_img, TRUE, FALSE);
		DrawRotaGraph(1100, 500, sparkling_size, sparkling_radian, sparkling_img, TRUE, FALSE);
		DrawRotaGraph(900, 400, sparkling_size, sparkling_radian, sparkling_img, TRUE, FALSE);
		DrawRotaGraph(910, 570, sparkling_size, sparkling_radian, sparkling_img, TRUE, FALSE);
		DrawRotaGraph(1170, 330, sparkling_size, sparkling_radian, sparkling_img, TRUE, FALSE);
	}
	else
	{
		// つるはし画像
		DrawRotaGraph((int)pickaxe_x, (int)pickaxe_y, 1.2, radian, pickaxe_img, TRUE, FALSE);
	}

	//int ax, ay;
	//GetMousePoint(&ax, &ay);
	//DrawFormatString(1000, 10, 0xffff00, "%d,%d", ax, ay);

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
	if (swing_se_cnt <= 0)
	{
		// つるはしが飛んでくる音
		if (CheckSoundMem(swing_se) == FALSE)
		{
			PlaySoundMem(swing_se, DX_PLAYTYPE_BACK);
		}
		swing_se_cnt = 32;
	}
	else
	{
		swing_se_cnt--;
	}

	// タイトルロゴを隠している岩と現在のつるはしとの距離
	distance_x = crack_x - pickaxe_x;
	distance_y = crack_y - pickaxe_y;

	// 平方根を使って距離を求める
	distance = sqrt(distance_x * distance_x + distance_y * distance_y);

	pickaxe_x += distance_x / distance * 3.5;
	pickaxe_y += distance_y / distance * 3.5;

	start_x = (float)pickaxe_x;
	start_y = (float)pickaxe_y;

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

// 岩にひびが入るアニメーション
void TitleScene::CrackRock()
{
	// つるはしでたたく音
	if (CheckSoundMem(decision_se) == FALSE)
	{
		PlaySoundMem(decision_se, DX_PLAYTYPE_BACK);
	}

	// 岩にひびが入る音
	if (CheckSoundMem(crack_se) == FALSE)
	{
		PlaySoundMem(crack_se, DX_PLAYTYPE_BACK);
	}

	if (rock_img_num < 2)
	{
		// 7fで画像切り替え
		rock_img_num = (anim_cnt - (rock_braek_timer - 10)) / 7;
	}

	if ((anim_cnt - (rock_braek_timer - 10)) / 7 == 3)
	{
		crack_rock_flg = true;
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
	start_y = (float)pickaxe_y;
	count = 0;
	tmp_sin = 0.0f;
	degree = 0.0;
	radian = (double)DEGREE_RADIAN(degree);
	text_up_flg = false;
}

// テキストを下から上に出す処理
void TitleScene::MoveText()
{
	tmp_sin = sinf((float)M_PI * 2.0f / 60.0f * (float)count);
	pickaxe_y = start_y - tmp_sin * 400.0f;
	start_text_y = tmp_start_text_y - tmp_sin * 400.0f;
	end_text_y = tmp_end_text_y - tmp_sin * 400.0f;

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
	if (pickaxe_y <= 400.0)
	{
		//pickaxe_x = 300.0;
		pickaxe_y += 5.0;
		start_text_y += 5.0;
		end_text_y += 5.0;
	}
	else
	{
		//pickaxe_x = 400.0;
		pickaxe_y = 400.0;
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

// 岩が崩れるアニメーション
void TitleScene::RockCollapses()
{
	// 岩が崩れる音
	if (CheckSoundMem(collapse_se) == FALSE)
	{
		PlaySoundMem(collapse_se, DX_PLAYTYPE_BACK);
	}

	move_x += 1;
	move_y += 15;
	if (rock_degree < 360.0)
	{
		// 岩の破片画像回転
		rock_degree += 1.0;
	}
	else
	{
		rock_degree = 0.0;
	}
}

// つるはし落下アニメーション
void TitleScene::PickaxeFalling()
{
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
			tmp_sin = sinf((float)M_PI * 2 / 60 * count);
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

// きらきらアニメーション
void TitleScene::SparklingAnimation()
{
	sparkling_anim_cnt++;

	// サイズ変更
	if (sparkling_anim_cnt <= 60)
	{
		sparkling_size += 0.01;
	}
	else
	{
		sparkling_size -= 0.01;
		if (sparkling_size <= 0.0)
		{
			sparkling_anim_cnt = 0;
		}
	}

	// 回転
	if (sparkling_degree < 360.0)
	{
		sparkling_degree += 6.0;
	}
	else
	{
		sparkling_degree = 0.0;
	}
	sparkling_radian = (double)DEGREE_RADIAN(sparkling_degree);

}
